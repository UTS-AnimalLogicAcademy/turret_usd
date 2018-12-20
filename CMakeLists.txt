cmake_minimum_required (VERSION 3.2)

macro(set_option option value)
    set(${option} ${value} CACHE INTERNAL ""FORCE)
endmacro()
set_option(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

# boost
set_option(BOOST_ROOT $ENV{REZ_BOOST_ROOT})

# tbb
set_option(TBB_ROOT_DIR $ENV{REZ_TBB_ROOT})
set_option(TBB_INCLUDE_DIR $ENV{REZ_TBB_ROOT}/include)
set_option(TBB_LIBRARY $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/)
set_option(TBB_LIBRARY $ENV{TBB_LIBRARIES})

set_option(PXR_BUILD_IMAGING OFF)
set_option(PXR_BUILD_USD_IMAGING OFF)

add_subdirectory("source")