set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE turretResolver)

find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)
if(WIN32)
    find_package(Boost REQUIRED)
endif(WIN32)

if(${USD_LIB_VARIANT} STREQUAL "HDK")
message("-- Building turret-usd for SideFX HDK USD libs")
set(TURRET_USD_LIB_DIR $ENV{HOUDINI_ROOT}/dsolib)
set(TURRET_USD_INC_DIR $ENV{HOUDINI_ROOT}/toolkit/include)
set(TURRET_USD_LIBS pxr_usd_ms )

elseif(${USD_LIB_VARIANT} STREQUAL "PXR")
message("-- Building turret-usd for Pixar USD libs")
set(TURRET_USD_LIB_DIR $ENV{REZ_USD_ROOT}/lib)
set(TURRET_USD_INC_DIR $ENV{REZ_USD_ROOT}/include)
set(TURRET_USD_LIBS 
    arch 
    tf 
    plug 
    vt 
    ar
)

elseif(${USD_LIB_VARIANT} STREQUAL "PXR_MONOLITHIC")
message("-- Building turret-usd for monlithic Pixar USD libs")
set(TURRET_USD_LIB_DIR $ENV{REZ_USD_ROOT}/lib)
set(TURRET_USD_INC_DIR $ENV{REZ_USD_ROOT}/include)
set(TURRET_USD_LIBS usd_ms )

endif()

link_directories(
        ${TURRET_USD_LIB_DIR}
        $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/
)

include_directories(
        ${TURRET_INCLUDES}
        ${PC_LIBZMQ_INCLUDE_DIRS}
        ${CPPZMQ_INCLUDE_DIRS}
        )

if(WIN32)
    link_directories($ENV{PYTHON_LIBS})
    link_libraries(wsock32.lib
        ws2_32.lib
        Iphlpapi.lib
        )
endif(WIN32)

pxr_plugin(${PXR_PACKAGE}
    LIBRARIES
        ${TURRET_USD_LIBS}
        ${Boost_PYTHON_LIBRARY}
        ${TURRET_LIBRARY}

    INCLUDE_DIRS
        ${TURRET_USD_INC_DIR}
        $ENV{REZ_TBB_ROOT}/include
        ${Boost_INCLUDE_DIRS}

    PUBLIC_HEADERS
        turretResolver.h

    CPPFILES
        turretResolver.cpp

    RESOURCE_FILES
        plugInfo.json
)
