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


#include "zmqClient.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {
    usd_zmq::zmqClient g_zmq;
}

AR_DEFINE_RESOLVER(AlaResolver, ArResolver);


/*static TfStaticData<std::vector<std::string>> _SearchPath;

struct AlaResolver::_Cache
{
    using _PathToResolvedPathMap = 
        tbb::concurrent_hash_map<std::string, std::string>;
    _PathToResolvedPathMap _pathToResolvedPathMap;
};*/

AlaResolver::AlaResolver() : ArDefaultResolver()
{
  
    /*std::cout << "AlaResolver constructor" << "\n";

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
    }*/
}

AlaResolver::~AlaResolver()
{
    
}

/*void
AlaResolver::SetDefaultSearchPath(
    const std::vector<std::string>& searchPath)
{
    *_SearchPath = searchPath;
}*/

/*std::string
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
}*/


/*static std::string
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
        }AR_DEFINE_RESOLVER

        return std::string();
    }

    return _Resolve(std::string(), path);
}*/

std::string
AlaResolver::Resolve(const std::string& path)
{
    return AlaResolver::ResolveWithAssetInfo(path, /* assetInfo = */ nullptr);
}

std::string
AlaResolver::ResolveWithAssetInfo(const std::string& path, ArAssetInfo* assetInfo) {
    if(g_zmq.matches_schema(path)) {
        return g_zmq.resolve_name(path);
    } else {
        return ArDefaultResolver::ResolveWithAssetInfo(path, assetInfo);
    }
}


void
AlaResolver::UpdateAssetInfo(
    const std::string& identifier,
    const std::string& filePath,
    const std::string& fileVersion,
    ArAssetInfo* resolveInfo)
{
    ArDefaultResolver::UpdateAssetInfo(identifier, filePath, fileVersion, resolveInfo);
}

VtValue
AlaResolver::GetModificationTimestamp(
    const std::string& path,
    const std::string& resolvedPath)
{
    return ArDefaultResolver::GetModificationTimestamp(path, resolvedPath);
}

bool 
AlaResolver::FetchToLocalResolvedPath(
    const std::string& path,
    const std::string& resolvedPath)
{
    //std::cout << "Path: " << path << "\n\n";
    //std::cout << "Resolved Path: " << resolvedPath << "\n\n";
    if(g_zmq.matches_schema(path)) {
        std::cout << "Fetching local\n";
        return true;
    } else {
        return true;
    }
}


/*AlaResolver::_CachePtr 
AlaResolver::_GetCurrentCache()
{
    _CachePtrStack& cacheStack = _threadCacheStack.local();
    return (cacheStack.empty() ? _CachePtr() : cacheStack.back());
}*/

std::string
AlaResolver::GetExtension(const std::string& path)
{
    if(g_zmq.matches_schema(path)) {   
        return "usd";
    }
    return ArDefaultResolver::GetExtension(path);
}

PXR_NAMESPACE_CLOSE_SCOPE
