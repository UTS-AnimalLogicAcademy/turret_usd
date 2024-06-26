cmake_minimum_required (VERSION 3.2)

set(Python_ROOT_DIR $ENV{REZ_PYTHON_ROOT}/miniconda$ENV{REZ_PYTHON_MAJOR_VERSION})
set(Python_INCLUDE_DIR "$ENV{PYTHON_INCLUDE_DIRS}")
#set(Python_LIBRARY "$ENV{PYTHON_LIBRARIES}")

set(REQUIRED_PY_VERSION $ENV{REZ_PYTHON_MAJOR_VERSION}.$ENV{REZ_PYTHON_MINOR_VERSION})

include(CMakePrintHelpers)
cmake_print_variables(Python_ROOT_DIR)

if(WIN32)
        add_definitions( -DBOOST_ALL_NO_LIB )
endif(WIN32)

set(CMAKE_MODULE_PATH
   ${CMAKE_SOURCE_DIR}/cmake
   ${CMAKE_MODULE_PATH}
)

macro(set_option option value)
    set(${option} ${value} CACHE INTERNAL ""FORCE)
endmacro()

# At ALA, our usd_houdini_hdk package sets an env var, which we use to automatically
# select the correct USD lib when building variants:
if(DEFINED ENV{USE_HDK_USD})
    message(1)
    if(DEFINED ENV{USE_HDK_MONOLITHIC_USD})
        message(2)
        if($ENV{USE_HDK_MONOLITHIC_USD} STREQUAL "1")
            message(3)
            set_option(USD_LIB_VARIANT HDK_MONOLITHIC)
        else()
            message(4)
            set_option(USD_LIB_VARIANT HDK)
        endif()

    else()
        message(5)
    endif()

elseif(DEFINED ENV{USE_KATANA_USD})
    set_option(USD_LIB_VARIANT KATANA)

elseif(DEFINED ENV{USE_MAYA_USD})
    set_option(USD_LIB_VARIANT MAYA)

elseif(DEFINED ENV{USE_NUKE_USD})
    set_option(USD_LIB_VARIANT NUKE)

elseif(DEFINED ENV{REZ_USD_MONOLITHIC_ROOT})
    set_option(USD_LIB_VARIANT PXR_MONOLITHIC)

elseif(DEFINED ENV{USE_MARI_USD})
    set_option(USD_LIB_VARIANT MARI)

else()
    set_option(USD_LIB_VARIANT PXR)
endif()

cmake_print_variables(USD_LIB_VARIANT)

set_option(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

if(UNIX)
        # jemalloc
        if(${USD_LIB_VARIANT} STREQUAL "HDK_MONOLITHIC")
            set_option(PXR_MALLOC_LIBRARY $ENV{HOUDINI_LOCATION}/../dsolib/libjemalloc.so)
        else()
            set_option(PXR_MALLOC_LIBRARY $ENV{REZ_JEMALLOC_ROOT}/lib/libjemalloc.so)
        endif()
endif(UNIX)

# boost
set_option(BOOST_ROOT "$ENV{REZ_BOOST_ROOT}")

# tbb
set_option(TBB_ROOT_DIR "$ENV{REZ_TBB_ROOT}")
set_option(TBB_INCLUDE_DIR "$ENV{REZ_TBB_ROOT}/include")
set_option(TBB_LIBRARY "$ENV{TBB_LIBRARIES}")

set_option(PXR_BUILD_IMAGING OFF)
set_option(PXR_BUILD_USD_IMAGING OFF)

add_subdirectory("source")
