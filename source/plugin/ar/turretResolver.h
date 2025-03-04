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

#include "pxr/pxr.h"
#include "pxr/usd/ar/api.h"
#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/defaultResolver.h"

#include <tbb/enumerable_thread_specific.h>

#include <memory>
#include <string>
#include <vector>

#include <turretClient.h>
#include <turretLogger.h>

PXR_NAMESPACE_OPEN_SCOPE

class TurretResolver
    : public ArDefaultResolver
{
    public:
        TurretResolver();
        AR_API
        virtual ~TurretResolver();

    protected:
        AR_API
        std::string _GetExtension(const std::string& assetPath) const override;
        AR_API
        ArResolvedPath _Resolve(const std::string& assetPath) const override;
        AR_API
        ArAssetInfo _GetAssetInfo(const std::string& assetPath,
            const ArResolvedPath& resolvedPath) const override;
        AR_API
        ArTimestamp _GetModificationTimestamp(
            const std::string& assetPath,
            const ArResolvedPath& resolvedPath) const override;

    private:
        mutable turret_client::turretClient m_turretClient;
        bool m_suppressAssetWarnings = false;
        const char *m_defaultUSD;
};

PXR_NAMESPACE_CLOSE_SCOPE


