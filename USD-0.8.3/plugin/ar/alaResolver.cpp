#include "alaResolver.h"

#include "pxr/pxr.h"
#include "pxr/usd/ar/defineResolver.h"
#include "pxr/usd/ar/assetInfo.h"
#include "pxr/usd/ar/resolverContext.h"

#include "pxr/base/arch/fileSystem.h"
#include "pxr/base/arch/systemInfo.h"
#include "pxr/base/tf/getenv.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/pathUtils.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/base/vt/value.h"

#include <tbb/concurrent_hash_map.h>
#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

AR_DEFINE_RESOLVER(AlaResolver, ArResolver);

static bool
_IsFileRelative(const std::string& path) {
    return path.find("./") == 0 || path.find("../") == 0;
}

static TfStaticData<std::vector<std::string>> _SearchPath;

struct AlaResolver::_Cache
{
    using _PathToResolvedPathMap = 
        tbb::concurrent_hash_map<std::string, std::string>;
    _PathToResolvedPathMap _pathToResolvedPathMap;
};

AlaResolver::AlaResolver()
{
  
    std::cout << "AlaResolver constructor" << std::endl;

    std::vector<std::string> searchPath = *_SearchPath;

    //    const std::string envPath = TfGetenv("PXR_AR_DEFAULT_SEARCH_PATH");
    const std::string envPath = TfGetenv("ALA_AR_DEFAULT_SEARCH_PATH");
    if (!envPath.empty()) {
        const std::vector<std::string> envSearchPath = 
            TfStringTokenize(envPath, ARCH_PATH_LIST_SEP);
        searchPath.insert(
            searchPath.end(), envSearchPath.begin(), envSearchPath.end());
    }

    _searchPath.reserve(searchPath.size());
    for (const std::string& p : searchPath) {
        if (p.empty()) {
            continue;
        }

        const std::string absPath = TfAbsPath(p);
        if (absPath.empty()) {
            TF_WARN(
                "Could not determine absolute path for search path prefix "
                "'%s'", p.c_str());
            continue;
        }

        _searchPath.push_back(absPath);
    }
}

AlaResolver::~AlaResolver()
{
}

void
AlaResolver::SetDefaultSearchPath(
    const std::vector<std::string>& searchPath)
{
    *_SearchPath = searchPath;
}

void
AlaResolver::ConfigureResolverForAsset(const std::string& path)
{
    // no configuration takes place in search path resolver
}

bool
AlaResolver::IsRelativePath(const std::string& path)
{
    return (!path.empty() && TfIsRelativePath(path));
}

bool
AlaResolver::IsRepositoryPath(const std::string& path)
{
    return false;
}

std::string
AlaResolver::AnchorRelativePath(
    const std::string& anchorPath, 
    const std::string& path)
{
    if (TfIsRelativePath(anchorPath) ||
        !AlaResolver::IsRelativePath(path) ||
        !_IsFileRelative(path)) {
        return path;
    }

    // Ensure we are using forward slashes and not back slashes.
    std::string forwardPath = anchorPath;
    std::replace(forwardPath.begin(), forwardPath.end(), '\\', '/');

    // If anchorPath does not end with a '/', we assume it is specifying
    // a file, strip off the last component, and anchor the path to that
    // directory.
    const std::string anchoredPath = TfStringCatPaths(
        TfStringGetBeforeSuffix(forwardPath, '/'), path);
    return TfNormPath(anchoredPath);
}

bool
AlaResolver::IsSearchPath(const std::string& path)
{
    return IsRelativePath(path) && !_IsFileRelative(path);
}

std::string
AlaResolver::GetExtension(const std::string& path)
{
    return TfGetExtension(path);
}

std::string
AlaResolver::ComputeNormalizedPath(const std::string& path)
{
    return TfNormPath(path);
}

std::string
AlaResolver::ComputeRepositoryPath(const std::string& path)
{
    return std::string();
}

static std::string
_Resolve(
    const std::string& anchorPath,
    const std::string& path)
{
    std::string resolvedPath = path;
    if (!anchorPath.empty()) {
        // XXX - CLEANUP:
        // It's tempting to use AnchorRelativePath to combine the two
        // paths here, but that function's file-relative anchoring
        // causes consumers to break. 
        // 
        // Ultimately what we should do is specify whether anchorPath 
        // in both Resolve and AnchorRelativePath can be files or directories 
        // and fix up all the callers to accommodate this.
        resolvedPath = TfStringCatPaths(anchorPath, path);
    }
    return TfPathExists(resolvedPath) ? resolvedPath : std::string();
}

std::string
AlaResolver::_ResolveNoCache(const std::string& path)
{

  std::cout << "\nfoobar\n";

    if (path.empty()) {
        return path;
    }

    if (IsRelativePath(path)) {
        // First try to resolve relative paths against the current
        // working directory.
        std::string resolvedPath = _Resolve(ArchGetCwd(), path);
        if (!resolvedPath.empty()) {
            return resolvedPath;
        }

        // If that fails and the path is a search path, try to resolve
        // against each directory in the specified search paths.
        if (IsSearchPath(path)) {
            for (const auto& searchPath : _searchPath) {
                resolvedPath = _Resolve(searchPath, path);
                if (!resolvedPath.empty()) {
                    return resolvedPath;
                }
            }
        }

        return std::string();
    }

    return _Resolve(std::string(), path);
}

std::string
AlaResolver::Resolve(const std::string& path)
{
    return ResolveWithAssetInfo(path, /* assetInfo = */ nullptr);
}

std::string
AlaResolver::ResolveWithAssetInfo(
    const std::string& path, 
    ArAssetInfo* assetInfo)
{
    if (path.empty()) {
        return path;
    }

    if (_CachePtr currentCache = _GetCurrentCache()) {
        _Cache::_PathToResolvedPathMap::accessor accessor;
        if (currentCache->_pathToResolvedPathMap.insert(
                accessor, std::make_pair(path, std::string()))) {
            accessor->second = _ResolveNoCache(path);
        }
        return accessor->second;
    }

    return _ResolveNoCache(path);
}

std::string
AlaResolver::ComputeLocalPath(const std::string& path)
{
    return path.empty() ? path : TfAbsPath(path);
}

void
AlaResolver::UpdateAssetInfo(
    const std::string& identifier,
    const std::string& filePath,
    const std::string& fileVersion,
    ArAssetInfo* resolveInfo)
{
    if (resolveInfo) {
        if (!fileVersion.empty()) {
            resolveInfo->version = fileVersion;
        }
    }
}

VtValue
AlaResolver::GetModificationTimestamp(
    const std::string& path,
    const std::string& resolvedPath)
{
    // Since the default resolver always resolves paths to local
    // paths, we can just look at the mtime of the file indicated
    // by resolvedPath.
    double time;
    if (ArchGetModificationTime(resolvedPath.c_str(), &time)) {
        return VtValue(time);
    }
    return VtValue();
}

bool 
AlaResolver::FetchToLocalResolvedPath(
    const std::string& path,
    const std::string& resolvedPath)
{
    // AlaResolver always resolves paths to a file on the
    // local filesystem. Because of this, we know the asset specified 
    // by the given path already exists on the filesystem at 
    // resolvedPath, so no further data fetching is needed.
    return true;
}

bool
AlaResolver::CanWriteLayerToPath(
    const std::string& path,
    std::string* whyNot)
{
    return true;
}

bool
AlaResolver::CanCreateNewLayerWithIdentifier(
    const std::string& identifier, 
    std::string* whyNot)
{
    return true;
}

ArResolverContext 
AlaResolver::CreateDefaultContext()
{
    return ArResolverContext();
}

ArResolverContext 
AlaResolver::CreateDefaultContextForAsset(
    const std::string& filePath)
{
    return ArResolverContext();
}

ArResolverContext
AlaResolver::CreateDefaultContextForDirectory(
    const std::string& fileDirectory)
{
    return ArResolverContext();
}

void 
AlaResolver::RefreshContext(const ArResolverContext& context)
{
}

ArResolverContext
AlaResolver::GetCurrentContext()
{
    return ArResolverContext();
}

void 
AlaResolver::_BeginCacheScope(
    VtValue* cacheScopeData)
{
    // cacheScopeData is held by ArResolverScopedCache instances
    // but is only populated by this function, so we know it must 
    // be empty (when constructing a regular ArResolverScopedCache)
    // or holding on to a _CachePtr (when constructing an 
    // ArResolverScopedCache that shares data with another one).
    TF_VERIFY(cacheScopeData &&
              (cacheScopeData->IsEmpty() ||
               cacheScopeData->IsHolding<_CachePtr>()));

    _CachePtrStack& cacheStack = _threadCacheStack.local();

    if (cacheScopeData->IsHolding<_CachePtr>()) {
        cacheStack.push_back(cacheScopeData->UncheckedGet<_CachePtr>());
    }
    else {
        if (cacheStack.empty()) {
            cacheStack.push_back(std::make_shared<_Cache>());
        }
        else {
            cacheStack.push_back(cacheStack.back());
        }
    }

    *cacheScopeData = cacheStack.back();
}

void 
AlaResolver::_EndCacheScope(
    VtValue* cacheScopeData)
{
    _CachePtrStack& cacheStack = _threadCacheStack.local();
    if (TF_VERIFY(!cacheStack.empty())) {
        cacheStack.pop_back();
    }
}

AlaResolver::_CachePtr 
AlaResolver::_GetCurrentCache()
{
    _CachePtrStack& cacheStack = _threadCacheStack.local();
    return (cacheStack.empty() ? _CachePtr() : cacheStack.back());
}

void 
AlaResolver::_BindContext(
    const ArResolverContext& context,
    VtValue* bindingData)
{
}

void 
AlaResolver::_UnbindContext(
    const ArResolverContext& context,
    VtValue* bindingData)
{
}

PXR_NAMESPACE_CLOSE_SCOPE
