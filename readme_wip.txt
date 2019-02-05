
super hacky dump of notes to be tidied later

BUILDING

We use rez as a build tool, which handles variants nicely.  In package.py we specify the build variants, which defines packages that will be resolved at build time.  In order to automatically select the USD libary to link turret_usd against, our usd_houdini_hdk package exports the env var $USE_HDK_USD=1, which if present when building, will cause cmake to set the cmake variable USD_LIB_VARIANT to HDK (the default is PXR).  


For non-rez users, if you want to manually specify which USD library to link against, you can invoke it at the terminal like this:

1.  Do whatever you do to create the build environment (source a .sh file, or use global system installs etc)
2.  mkdir build;cd build
3.  cmake -DUSD_LIB_VARIANT=HDK ../source/
4.  make


As part of our rez build process, we define a parent CMakeLists.txt which sets some cmake variables using environment variables (generally package roots, library locations etc).  This lets us build simply by:
1.  rez-build -i


For non-rez users, if you want to specify these same variables from env vars to cmake as CLI args, this example may help:

cmake -DUSD_LIB_VARIANT=PXR -DPXR_MALLOC_LIBRARY=$REZ_JEMALLOC_ROOT/lib/libjemalloc.so -DBOOST_ROOT=$REZ_BOOST_ROOT -DTBB_ROOT_DIR=$REZ_TBB_ROOT -DTBB_INCLUDE_DIR=$REZ_TBB_ROOT/include -DTBB_LIBRARY=$REZ_TBB_ROOT/lib/intel64/gcc4.4;$TBB_LIBRARIES -DPXR_BUILD_IMAGING=OFF -DPXR_BUILD_USD_IMAGING=OFF ../source/