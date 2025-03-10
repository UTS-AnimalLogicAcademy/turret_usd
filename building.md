# Building turret_usd
At present, Linux is our primary supported build platform. There is now basic windows support but is not our primary focus.

## Requirements
 * turret_lib
 * libzmq-4.2.3
 * USD-24.08 - or any other version up to 24.08 that is built with AR 2.0
   * TBB (Same version as USD)
   * Boost (Same version as USD)
 * cmake-3.28

Other versions may work but are untested.  
NOTE: To build older versions of USD with USD AR 1.0, checkout the ar-1.0 branch.

### Linux
We use [rez](https://github.com/nerdvegas/rez) as a build tool, which handles variants nicely. In package.py we specify the build variants, which defines packages that will be resolved at build time. In order to automatically select the USD libary to link turret_usd against, our `usd_houdini_hdk` package exports the env var `$USE_HDK_USD=1`, which if present when building, will cause cmake to set the cmake variable `USD_LIB_VARIANT` to `HDK` (the default is `PXR`).  

#### Rez
As part of our rez build process, we define a parent CMakeLists.txt which sets some cmake variables using environment variables (generally package roots, library locations etc). This lets us build simply by:

1. `rez-build -i`

#### Non-Rez
For non-rez users, if you want to manually specify which USD library to link against, you can invoke it at the terminal like this:

1. Do whatever you do to create the build environment (source a .sh file, or use global system installs etc)
2. `mkdir build; cd build`
3. `cmake -DUSD_LIB_VARIANT=HDK ../source/`
4. `make ..`

For non-rez users, if you want to specify these same variables from env vars to cmake as CLI args, this example may help:

`cmake -DUSD_LIB_VARIANT=PXR -DPXR_MALLOC_LIBRARY=$REZ_JEMALLOC_ROOT/lib/libjemalloc.so -DBOOST_ROOT=$REZ_BOOST_ROOT -DTBB_ROOT_DIR=$REZ_TBB_ROOT -DTBB_INCLUDE_DIR=$REZ_TBB_ROOT/include -DTBB_LIBRARY=$REZ_TBB_ROOT/lib/intel64/gcc4.4;$TBB_LIBRARIES -DPXR_BUILD_IMAGING=OFF -DPXR_BUILD_USD_IMAGING=OFF ../source/`

### Windows

Environment Variables

Our initial windows build used the monolithic build. When the environment variable `USE_MONOLITHIC_USD` is set, cmake will link against `usd_ms`. This has only been tested on windows.

`LIBTURRET_ROOT=C:/path/to/turret-lib`
`REZ_USD_ROOT=C:/path/to/USD`
`REZ_BOOST_ROOT=C:/path/to/boost_root`
`REZ_TBB_ROOT=C:/path/to/USD/18.09.2/src/tbb2017_20170226oss`
`TBB_LIBRARIES=C:/path/to/USD_Source/src/tbb2017_20170226oss/lib/intel64/vc14`
`LIBZMQ_INCLUDE_DIR=C:/path/to/libzmq/include`
`LIBZMQ_LIB_DIR=C:/path/to/libzmq-v140-mt-4_3_2.lib`
`USD_LIB_VARIANT=PXR_MONOLITHIC`
