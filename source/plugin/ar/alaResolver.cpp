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
#include <string>


#include "zmqDispatch.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {
    usd_zmq::zmqDispatch g_zmq;
}

AR_DEFINE_RESOLVER(AlaResolver, ArResolver);


AlaResolver::AlaResolver() : ArDefaultResolver()
{
    std::cout << "ALA USD Resolver - Created Resolver\n\n";
}

AlaResolver::~AlaResolver()
{
    std::cout << "ALA USD Resolver - Destroyed Resolver\n\n";
}

std::string
AlaResolver::Resolve(const std::string& path)
{
    return AlaResolver::ResolveWithAssetInfo(path, /* assetInfo = */ nullptr);
}

std::string
AlaResolver::ResolveWithAssetInfo(const std::string& path, ArAssetInfo* assetInfo) {
    // Check if path provided is of tank schema
    if(g_zmq.matches_schema(path)) {
        std::string query = path;

        // Check for USD_ASSET_TIME env var
        const std::string envUsdAssetTime = TfGetenv("USD_ASSET_TIME");

        // If time var exists, append asset time to query
        if(!envUsdAssetTime.empty()) {
            query += "&time=" + envUsdAssetTime;
        }

        std::cout << "ALA USD Resolver - using ala usd resolver for file path: " << path << "\n\n";

        return g_zmq.resolve_name(query);
    } else {

        const char* env_p = std::getenv("ALA_USD_RESOLVER_LOG_LEVEL");
        const std::string env_s = std::string(env_p);
        if(env_s == "1"){
            std::cout << "ALA USD Resolver - using default resolver for file path: " << path << "\n\n";
        }


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
    return true;

    /*if(g_zmq.matches_schema(path)) {
        return true;
    } else {
        return true;
    }*/
}

std::string
AlaResolver::GetExtension(const std::string& path)
{
    if(g_zmq.matches_schema(path)) {   
        // TODO: Query tank for extension
        return "usd";
    }
    return ArDefaultResolver::GetExtension(path);
}

PXR_NAMESPACE_CLOSE_SCOPE
