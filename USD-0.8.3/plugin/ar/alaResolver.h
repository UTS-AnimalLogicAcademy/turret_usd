#include "pxr/pxr.h"
#include "pxr/usd/ar/api.h"
#include "pxr/usd/ar/resolver.h"

#include <tbb/enumerable_thread_specific.h>

#include <memory>
#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class AlaResolver
    : public ArResolver
{
public:
    AlaResolver();
    virtual ~AlaResolver();

    /// Set the default search path that will be used during asset
    /// resolution. This must be called before the first call
    /// to \ref ArGetResolver.
    AR_API
    static void SetDefaultSearchPath(
        const std::vector<std::string>& searchPath);

    // ArResolver overrides
    virtual void ConfigureResolverForAsset(const std::string& path) override;

    virtual std::string AnchorRelativePath(
        const std::string& anchorPath, 
        const std::string& path) override; 

    virtual bool IsRelativePath(const std::string& path) override;
    virtual bool IsRepositoryPath(const std::string& path) override;
    virtual bool IsSearchPath(const std::string& path) override;

    virtual std::string GetExtension(const std::string& path) override;

    virtual std::string ComputeNormalizedPath(const std::string& path) override;

    virtual std::string ComputeRepositoryPath(const std::string& path) override;

    virtual std::string ComputeLocalPath(const std::string& path) override;

    virtual std::string Resolve(const std::string& path) override;

    virtual std::string ResolveWithAssetInfo(
        const std::string& path, 
        ArAssetInfo* assetInfo) override;

    virtual void UpdateAssetInfo(
       const std::string& identifier,
       const std::string& filePath,
       const std::string& fileVersion,
       ArAssetInfo* assetInfo) override;

    virtual VtValue GetModificationTimestamp(
        const std::string& path,
        const std::string& resolvedPath) override;

    virtual bool FetchToLocalResolvedPath(
        const std::string& path,
        const std::string& resolvedPath) override;

    virtual bool CanWriteLayerToPath(
        const std::string& path,
        std::string* whyNot) override;

    virtual bool CanCreateNewLayerWithIdentifier(
        const std::string& identifier, 
        std::string* whyNot) override;

    virtual ArResolverContext CreateDefaultContext() override;

    virtual ArResolverContext CreateDefaultContextForAsset(
        const std::string& filePath) override;

    virtual ArResolverContext CreateDefaultContextForDirectory(
        const std::string& fileDirectory) override;

    virtual void RefreshContext(const ArResolverContext& context) override;

    virtual ArResolverContext GetCurrentContext() override;

protected:
    virtual void _BeginCacheScope(
        VtValue* cacheScopeData) override;

    virtual void _EndCacheScope(
        VtValue* cacheScopeData) override;

    virtual void _BindContext(
        const ArResolverContext& context,
        VtValue* bindingData) override;

    virtual void _UnbindContext(
        const ArResolverContext& context,
        VtValue* bindingData) override;

private:
    struct _Cache;
    using _CachePtr = std::shared_ptr<_Cache>;
    _CachePtr _GetCurrentCache();

    std::string _ResolveNoCache(const std::string& path);

private:
    std::vector<std::string> _searchPath;

    using _CachePtrStack = std::vector<_CachePtr>;
    using _PerThreadCachePtrStack = 
        tbb::enumerable_thread_specific<_CachePtrStack>;

    _PerThreadCachePtrStack _threadCacheStack;
};

PXR_NAMESPACE_CLOSE_SCOPE


