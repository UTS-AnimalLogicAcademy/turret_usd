//
// Copyright 2019 University of Technology, Sydney
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
// to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//   * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
//     the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <iostream>
#include <string>

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

#include "tbb/concurrent_hash_map.h"

#include "turretResolver.h"
#include "turretClient.h"

PXR_NAMESPACE_OPEN_SCOPE

AR_DEFINE_RESOLVER(TurretResolver, ArResolver);

TurretResolver::TurretResolver() : ArDefaultResolver(), m_turretClient("usd"), m_defaultUSD(std::getenv("DEFAULT_USD")) {
    std::cout << "TURRET USD Resolver - Created Resolver" << std::endl;

    const char *suppressAssetWarningsEnv = std::getenv("TURRET_USD_SUPPRESS_ASSET_NOT_FOUND");
    if(suppressAssetWarningsEnv && m_defaultUSD){
        std::cout << "TURRET USD Resolver - Suppressing asset not found warnings. Will load default USD path if asset not found: " << m_defaultUSD << std::endl;
        m_suppressAssetWarnings = true;
    }else if(suppressAssetWarningsEnv && !m_defaultUSD){
        std::cout << "TURRET USD Resolver - Cannot suppress asset not found warnings. DEFAULT_USD env var not set." << std::endl;
    }
}

TurretResolver::~TurretResolver() {
    std::cout << "TURRET USD Resolver - Destroyed Resolver" << std::endl;
}

ArResolvedPath TurretResolver::_Resolve(const std::string& assetPath) const{
    
    if(m_turretClient.matches_schema(assetPath)){
        std::string query = assetPath;

        // Check for USD_ASSET_TIME env var
        const std::string envUsdAssetTime = TfGetenv("USD_ASSET_TIME");

        // If time var exists, append asset time to query
        if(!envUsdAssetTime.empty()) {
            query += "&time=" + envUsdAssetTime;
        }

        std::string resolvedPath = m_turretClient.resolve_name(query);

        if(resolvedPath == "NOT_FOUND") {
            if(m_suppressAssetWarnings) {

                // Return default USD path to avoid spamming logs with warnings
                return ArResolvedPath(m_defaultUSD);
            }
            else {
                
                // Return empty resolved path (will generate warning)
                return ArResolvedPath();
            }
        }

        // turret_client::turretLogger::Instance()->Log("TURRET USD Resolver - using ala usd resolver for file path: " + query);
        return ArResolvedPath(resolvedPath);
    }
    else {
        return ArDefaultResolver::_Resolve(assetPath);
    }
}

ArTimestamp TurretResolver::_GetModificationTimestamp(
    const std::string& assetPath,
    const ArResolvedPath& resolvedPath) const{
    return ArDefaultResolver::_GetModificationTimestamp(assetPath, resolvedPath);
}

ArAssetInfo TurretResolver::_GetAssetInfo(const std::string& assetPath,
            const ArResolvedPath& resolvedPath) const {
            return ArDefaultResolver::_GetAssetInfo(assetPath,resolvedPath);
}

std::string TurretResolver::_GetExtension(const std::string& assetPath) const {
    if(m_turretClient.matches_schema(assetPath)){
        return "usd";
    }
    else{
        return ArDefaultResolver::_GetExtension(assetPath);
    }
}

PXR_NAMESPACE_CLOSE_SCOPE
