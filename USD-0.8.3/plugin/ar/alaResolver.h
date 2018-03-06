#include "pxr/pxr.h"
#include "pxr/usd/ar/api.h"
#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/defaultResolver.h"

#include <tbb/enumerable_thread_specific.h>

#include <memory>
#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class AlaResolver
    : public ArDefaultResolver
{
public:
    AlaResolver();
    virtual ~AlaResolver();

    /// Set the default search path that will be used during asset
    /// resolution. This must be called before the first call
    /// to \ref ArGetResolver.
    
    /*static void SetDefaultSearchPath(
        const std::vector<std::string>& searchPath);*/

    /*virtual std::string AnchorRelativePath(
        const std::string& anchorPath, 
        const std::string& path) override; */
AR_API
    virtual std::string GetExtension(const std::string& path) override;
    AR_API
    virtual std::string Resolve(const std::string& path) override;

AR_API
    virtual std::string ResolveWithAssetInfo(
        const std::string& path, 
        ArAssetInfo* assetInfo) override;
AR_API
    virtual void UpdateAssetInfo(
       const std::string& identifier,
       const std::string& filePath,
       const std::string& fileVersion,
       ArAssetInfo* assetInfo) override;
AR_API
    virtual VtValue GetModificationTimestamp(
        const std::string& path,
        const std::string& resolvedPath) override;
AR_API
    virtual bool FetchToLocalResolvedPath(
        const std::string& path,
        const std::string& resolvedPath) override;


private:
    //struct _Cache;
    //using _CachePtr = std::shared_ptr<_Cache>;
    //_CachePtr _GetCurrentCache();

    //std::string _ResolveNoCache(const std::string& path);

private:
    //std::vector<std::string> _searchPath;

    //using _CachePtrStack = std::vector<_CachePtr>;
    //using _PerThreadCachePtrStack = 
    //    tbb::enumerable_thread_specific<_CachePtrStack>;

    //_PerThreadCachePtrStack _threadCacheStack;
};

PXR_NAMESPACE_CLOSE_SCOPE


