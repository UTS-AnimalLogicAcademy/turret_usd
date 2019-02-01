@echo off

rd /s /q build

mkdir build
cd build

SET USE_MONOLITHIC_USD=True
SET LIBTURRET_ROOT=C:/Users/142738/software/turret-lib
SET PYTHON_LIBS=C:/Python27/libs

SET LIBZMQ_INCLUDE_DIR=C:/Users/142738/git/libzmq/include
SET LIBZMQ_LIB_DIR=C:/Users/142738/git/libzmq/build/lib/Release/libzmq-v140-mt-4_3_2.lib

SET REZ_BOOST_ROOT=C:/local/boost_1_61_0
SET REZ_TBB_ROOT=C:/Users/142738/software/USD/19.01/src/tbb2017_20170226oss
SET REZ_USD_ROOT=C:/Users/142738/software/USD/19.01
SET TBB_LIBRARIES=C:/Users/142738/software/USD/19.01/src/tbb2017_20170226oss/lib/intel64/vc14

cmake -DCMAKE_INSTALL_PREFIX="C:\Users\142738\software\turret-usd" -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config Release --target install -- /M:16

cd ..
