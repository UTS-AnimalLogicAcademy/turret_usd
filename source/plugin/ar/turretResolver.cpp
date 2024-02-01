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

TurretResolver::TurretResolver() : ArDefaultResolver(), m_turretClient("usd") {
    std::cout << "TURRET USD Resolver - Created Resolver\n\n";
}

TurretResolver::~TurretResolver() {
    std::cout << "TURRET USD Resolver - Destroyed Resolver\n\n";
}

ArResolvedPath TurretResolver::_Resolve(const std::string& assetPath) const{
    std::string query = assetPath;

    const auto path = ArDefaultResolver::_Resolve(assetPath);
    if(path){
        return path;
    }

    // Check for USD_ASSET_TIME env var
    const std::string envUsdAssetTime = TfGetenv("USD_ASSET_TIME");

    // If time var exists, append asset time to query
    if(!envUsdAssetTime.empty()) {
        query += "&time=" + envUsdAssetTime;
    }

    //turret_client::turretLogger::Instance()->Log("TURRET USD Resolver - using ala usd resolver for file path: " + query);
    return ArResolvedPath(m_turretClient.resolve_name(query));
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
    return "usd";
}

PXR_NAMESPACE_CLOSE_SCOPE
