# Building Turret-USD
At present, Linux is our primary supported build platform. There is now basic windows support but is not our primary focus.

## Requirements
 * turret-0.0.1
 * libzmq-4.2.3
 * USD-19.01
   * TBB (Same version as USD)
   * Boost (Same version as USD)
 * cmake-3.2

Other versions may work but are untested.  

### Linux

### Windows

Environment Variables

Our initial windows build used the monolithic build. When the environment variable `USE_MONOLITHIC_USD` is set, cmake will link against `usd_ms`. This has only been tested on windows.

LIBTURRET\_ROOT=C:/path/to/turret-lib
REZ\_USD\_ROOT=C:/path/to/USD
REZ\_BOOST\_ROOT=C:/path/to/boost\_root
REZ\_TBB\_ROOT=C:/path/to/USD/18.09.2/src/tbb2017\_20170226oss
TBB\_LIBRARIES=C:/path/to/USD\_Source/src/tbb2017\_20170226oss/lib/intel64/vc14
LIBZMQ\_INCLUDE\_DIR=C:/path/to/libzmq/include
LIBZMQ\_LIB\_DIR=C:/path/to/libzmq-v140-mt-4\_3\_2.lib
USD\_LIB\_VARIANT=PXR\_MONOLITHIC