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
We use [rez](https://github.com/nerdvegas/rez) as a build tool, which handles variants nicely. In package.py we specify the build variants, which defines packages that will be resolved at build time. In order to automatically select the USD libary to link turret_usd against, you can specify one of several environment variables in the vein of `$USE_{PACKAGE}_USD`. The currently supported options are as follows:
* #### Default - PXR USD (OpenUSD)
  * By default, `USD_LIB_VARAITN` is set to `PXR`. This sets up turret_usd to build with the Pixar USD (OpenUSD) libs.
  * Requires `$REZ_USD_ROOT` to point to the root directory of the USD install. (e.g. `~/usd/23.11`)
    * Sets `TURRET_USD_INC_DIR` to `$ENV{REZ_USD_ROOT}/include`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{REZ_USD_ROOT}/lib`
  * Requires `$REZ_USD_MAJOR_VERSION` to be set to the **major** version of the USD install. (e.g. USD 23.11 would have `$REZ_USD_MAJOR_VERSION` set to `23`)
    * Sets `TURRET_USD_LIBS` to `usd_{usd_lib_name}` or `{usd_lib_name}`, depending on the USD major version.
  * ##### `$REZ_USD_MONOLITHIC_ROOT`
    * If `REZ_USD_MONOLITHIC_ROOT`is set, overrides `USD_LIB_VARIANT` to `PXR_MONOLITHIC`. Designed to set up turret_usd to build with the Pixar (OpenUSD) **monolithic** USD lib.
    * `$REZ_USD_ROOT` does **not** need to be set if `REZ_USD_MONOLITHIC_ROOT` is set.
    * Requires `$REZ_USD_MONOLITHIC_ROOT` to point to the root directory of the USD install. (e.g. `~/usd/23.11`)
      * Sets `TURRET_USD_INC_DIR` to `$ENV{REZ_USD_MONOLITHIC_ROOT}/include`
      * Sets `TURRET_USD_LIB_DIR` to `$ENV{REZ_USD_MONOLITHIC_ROOT}/lib`
    * Overrides `TURRET_USD_LIBS` to `usd_ms`.
* #### `$USE_HDK_USD=1`
  * Sets `USD_LIB_VARIANT` to `HDK`. Designed to set up turret_usd to build with SideFX Houdini's USD libs.
  * Requires `$HOUDINI_ROOT` to point to the root directory of the preferred Houdini install.
    * Sets `TURRET_USD_INC_DIR` to `$ENV{HOUDINI_ROOT}/toolkit/include`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{HOUDINI_ROOT}/dsolib`
  * Sets `TURRET_USD_LIBS` to `pxr_{usd_lib_name}`.
  * ##### `$USE_HDK_MONOLITHIC_USD=1`
    * If `USE_HDK_USD` **and** `USE_HDK_MONOLITHIC_USD` are set, overrides `USD_LIB_VARIANT` to `HDK_MONOLITHIC`. Designed to set up turret_usd to build with SideFX Houdini's **monolithic** USD lib.
    * Overrides `TURRET_USD_LIBS` to `pxr_usd_ms`.
* #### `$USE_KATANA_USD=1`
  * Sets `USD_LIB_VARIANT` to `KATANA`. Designed to set up turret_usd to build with Foundry's internal Katana FnUSD libs.
  * Requires `$KATANA_HOME` to point to the root directory of the preferred Katana install. (e.g. `/opt/Foundry/Katana7.0v4`)
    * Sets `TURRET_USD_INC_DIR` to `$ENV{KATANA_HOME}/external/FnUSD/include`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{KATANA_HOME}/bin`
  * Requires `$REZ_KATANA_MAJOR_VERSION` to be set to the **major** version of the preferred Katana install. (e.g. Katana 3.5v2 would have `$REZ_KATANA_MAJOR_VERSION` set to `3`)
    * Sets `TURRET_USD_LIBS` to `fn{usd_lib_name}` or `Fn{usd_lib_name}`, depending on the Katana major version.
* #### `$USE_NUKE_USD=1`
  * Sets `USD_LIB_VARIANT` to `NUKE`. Designed to set up turret_usd to build with Foundry internal Nuke FnUSD libs.
  * Requires `$NUKE_USD_INCLUDE_DIR` to point to the directory of the FnUSD headers within the preferred Nuke install. (e.g. `/opt/Foundry/Nuke15.1v2/FnUSD/include/`)
    * If your Nuke install does not include the headers for FnUSD, you may build your own copy of the same version of USD as your Nuke install and use those headers instead.
      * Building USD: [https://github.com/PixarAnimationStudios/OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD)
      * Nuke USD versions can be found here: [https://learn.foundry.com/nuke/15.1v1/content/misc/studio_third_party_libraries.html](https://learn.foundry.com/nuke/15.1v1/content/misc/studio_third_party_libraries.html)
        * The version number in the above URL can be changed to find your preferred version of Nuke.
        * You may also be able to use the FnUSD headers from an installed version of Katana with the same USD version as your preferred Nuke install.
  * Requires `$NUKE_USD_LIB_DIR` to point to the directory of the FnUSD libraries within the preferred Nuke install. (e.g. `/opt/Foundry/Nuke15.1v2/FnUSD/lib/`)
    * Sets `TURRET_USD_INC_DIR` to `$ENV{NUKE_USD_INCLUDE_DIR}`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{NUKE_USD_LIB_DIR}`
  * Requires `$REZ_NUKE_MAJOR_VERSION` to be set to the **major** version of the preferred Nuke install. (e.g. Nuke 15.1v1 would have `$REZ_NUKE_MAJOR_VERSION` set to `15`)
    * Sets `TURRET_USD_LIBS` to `usd_{usd_lib_name}`, `fn{usd_lib_name}`, or `{usd_lib_name}`, depending on the Nuke major version.
* #### `$USE_MARI_USD=1`
  * Sets `USD_LIB_VARIANT` to `MARI`. Designed to set up turret_usd to build with Foundry internal Mari FnUSD libs.
    * **Important**: Unfortunately, Mari's install does not come with the headers for FnUSD, and therefore you must provide the headers from your own build of the same version of USD, or a Katana install with the same USD version as the preferred Mari version. Nuke installs do not require all the necessary headers for Mari.
      * Building USD: [https://github.com/PixarAnimationStudios/OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD)
      * Mari USD versions can be found here: [https://learn.foundry.com/mari/6.0/Content/user_guide/appendix_c/third_party_licenses.html](https://learn.foundry.com/mari/6.0/Content/user_guide/appendix_c/third_party_licenses.html)
      * Katana USD versions can be found here: [https://learn.foundry.com/katana/4.5/dev-guide/ExternalSoftware.html](https://learn.foundry.com/katana/4.5/dev-guide/ExternalSoftware.html)
        * The version numbers in the above URLs can be changed to find your preferred versions of Mari/Katana.
  * Requires `$MARI_LOCATION` to point to the root directory of the preferred Mari install. (e.g. `/opt/Foundry/Mari6.0v2`)
  * Requires `$MARI_FNUSD_INCLUDE_DIR` to point to the directory of the FnUSD headers within a Katana install with the same USD version as the preferred Mari version. (e.g. `/opt/Foundry/Katana6.0v1/external/FnUSD/include`)
    * Sets `TURRET_USD_INC_DIR` to `$ENV{MARI_FNUSD_INCLUDE_DIR}`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{MARI_LOCATION}/3rdParty/lib`
    * Sets `TURRET_USD_LIBS` to `fn{usd_lib_name}`.
* #### `$USE_MAYA_USD=1`
  * Sets `USD_LIB_VARIANT` to `MAYA`. Designed to set up turret_usd to build with Autodesks's Maya USD libs.
    * **Important**: Unfortunately, Maya USD's install does not come with the headers for USD, and therefore you must provide the headers from your own build of the same version of USD.
      * Building USD: [https://github.com/PixarAnimationStudios/OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD)
      * The USD version for which Maya USD is built for different Maya versions can be found here: [https://github.com/Autodesk/maya-usd/releases](https://github.com/Autodesk/maya-usd/releases)
  * Requires `$MAYA_USD_INCLUDE_DIR` to point to the directory of the USD headers within your USD install. (e.g. `~/usd/23.11/include`)
  * Requires `$MAYA_USD_ROOT` to point to the root directory of the Maya USD installed for your preferred version Maya. (e.g. `/usr/autodesk/mayausd/maya2025/0.28.0_202404152327-48d2ddb` for Maya 2025 and Maya USD 0.28.0)
    * Sets `TURRET_USD_INC_DIR` to `$$ENV{MAYA_USD_INCLUDE_DIR}`
    * Sets `TURRET_USD_LIB_DIR` to `$ENV{MAYA_USD_ROOT}/mayausd/USD/lib`
  * Requires `$REZ_MAYA_MAJOR_VERSION` to be set to the **major** version of the preferred Maya install. (e.g. Maya 2025.3 would have `$REZ_MAYA_MAJOR_VERSION` set to `2025`)
    * Sets `TURRET_USD_LIBS` to `usd_{usd_lib_name}` or `{usd_lib_name}`, depending on the Maya major version.
 

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

You can specify a Python version using the `-DREQUIRED_PY_VERSION` flag. (e.g. `-DREQUIRED_PY_VERSION=3.9` will tell CMake to look for a Python 3.9 install)

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

### C++ 11 ABI
If the `$CXX11_ABI_IGNORE` environment variable is set for a particular build, the `_GLIBCXX_USE_CXX11_ABI=0` flag will be set for that build.
This is useful when building against a DCC that was built with the old C++ ABI.
