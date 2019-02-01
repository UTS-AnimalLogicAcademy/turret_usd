set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE turretResolver)

find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)
if(MSVC)
    find_package(Boost REQUIRED)
endif(MSVC)

link_directories($ENV{REZ_USD_ROOT}/lib
        $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/
        ${TURRET_LIBRARY}
)

link_libraries(${TURRET_LIBRARY})

if(MSVC)
    link_directories($ENV{PYTHON_LIBS})
    link_libraries(wsock32.lib
        ws2_32.lib
        Iphlpapi.lib
        )
endif(MSVC)

include_directories(
        ${TURRET_INCLUDES}
        ${PC_LIBZMQ_INCLUDE_DIRS}
        ${CPPZMQ_INCLUDE_DIRS}
        )

if($ENV{USE_MONOLITHIC_USD})
    message("Building Turret-USD Plugin with monolithic build")
    pxr_plugin(${PXR_PACKAGE}
        LIBRARIES
            usd_ms
            ${Boost_PYTHON_LIBRARY}
            ${TURRET_LIBRARY}

        INCLUDE_DIRS
            $ENV{REZ_USD_ROOT}/include
            $ENV{REZ_TBB_ROOT}/include
            ${Boost_INCLUDE_DIRS}

        PUBLIC_HEADERS
            turretResolver.h

        CPPFILES
            turretResolver.cpp

        RESOURCE_FILES
            plugInfo.json
    )
else()
    message("Building Turret-USD Plugin with individual libraries")
    pxr_plugin(${PXR_PACKAGE}
        LIBRARIES
            arch
            tf
            plug
            vt
            ar
            ${Boost_PYTHON_LIBRARY}

        INCLUDE_DIRS
            $ENV{REZ_USD_ROOT}/include
            $ENV{REZ_TBB_ROOT}/include
            ${Boost_INCLUDE_DIRS}

        PUBLIC_HEADERS
            turretResolver.h

        CPPFILES
            turretResolver.cpp

        RESOURCE_FILES
            plugInfo.json
    )
endif()