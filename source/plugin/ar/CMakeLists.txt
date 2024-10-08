set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE turretResolver)

find_package(Turret REQUIRED)
find_package(ZeroMQ REQUIRED)
if(WIN32)
    find_package(Boost REQUIRED)
endif(WIN32)

if(${USD_LIB_VARIANT} STREQUAL "HDK_MONOLITHIC")
message("-- Building turret-usd for monolithic SideFX HDK USD libs")
set(TURRET_USD_LIB_DIR $ENV{HOUDINI_ROOT}/dsolib)
set(TURRET_USD_INC_DIR $ENV{HOUDINI_ROOT}/toolkit/include)
set(TURRET_USD_LIBS pxr_usd )

elseif(${USD_LIB_VARIANT} STREQUAL "HDK")
message("-- Building turret-usd for SideFX HDK USD libs")
set(TURRET_USD_LIB_DIR $ENV{HOUDINI_ROOT}/dsolib)
set(TURRET_USD_INC_DIR $ENV{HOUDINI_ROOT}/toolkit/include)
set(TURRET_USD_LIBS
    pxr_arch
    pxr_tf
    pxr_plug
    pxr_vt
    pxr_ar
)

elseif(${USD_LIB_VARIANT} STREQUAL "KATANA")
message("-- Building turret-usd for Katana USD libs")
set(TURRET_USD_LIB_DIR $ENV{KATANA_HOME}/bin)
set(TURRET_USD_INC_DIR $ENV{KATANA_HOME}/external/FnUSD/include)
if($ENV{REZ_KATANA_MAJOR_VERSION} GREATER 3)
set(TURRET_USD_LIBS
        fnarch
        fntf
        fnplug
        fnvt
        fnar
        )
else()
set(TURRET_USD_LIBS
        Fnarch
        Fntf
        Fnplug
        Fnvt
        Fnar
        )
endif()

elseif(${USD_LIB_VARIANT} STREQUAL "MV")
    message("-- Building turret-usd for Multiverse USD libs")
    set(TURRET_USD_LIB_DIR $ENV{MULTIVERSE_HOME}/lib/python/mvpxr)
    set(TURRET_USD_INC_DIR $ENV{MULTIVERSE_HOME}/include?)
    set(TURRET_USD_LIBS
            _arch
            _tf
            _plug
            _vt
            _ar
            )


elseif(${USD_LIB_VARIANT} STREQUAL "NUKE")
            message("-- Building turret-usd for Nuke USD libs")
        set(TURRET_USD_LIB_DIR $ENV{NUKE_USD_LIB_DIR})
        set(TURRET_USD_INC_DIR $ENV{NUKE_USD_INCLUDE_DIR})
    if($ENV{REZ_NUKE_MAJOR_VERSION} GREATER 14)
        set(TURRET_USD_LIBS
                usd_arch
                usd_tf
                usd_plug
                usd_vt
                usd_ar
                )
    elseif($ENV{REZ_NUKE_MAJOR_VERSION} GREATER 13)
        set(TURRET_USD_LIBS
                fnarch
                fntf
                fnplug
                fnvt
                fnar
                )
    else()
        set(TURRET_USD_LIBS
                arch
                tf
                plug
                vt
                ar
                )
    endif()

elseif(${USD_LIB_VARIANT} STREQUAL "MARI")
    if($ENV{REZ_MARI_MAJOR_VERSION} GREATER 6)
    message("-- Building turret-usd for Mari USD libs")
    set(TURRET_USD_LIB_DIR $ENV{MARI_LOCATION}/3rdParty/lib)
    set(TURRET_USD_INC_DIR /opt/Foundry/Katana7.0v4/external/FnUSD/include)

    set(TURRET_USD_LIBS
            fnarch
            fntf
            fnplug
            fnvt
            fnar
            )

    elseif($ENV{REZ_MARI_MAJOR_VERSION} GREATER 5)
    message("-- Building turret-usd for Mari USD libs")
    set(TURRET_USD_LIB_DIR $ENV{MARI_LOCATION}/3rdParty/lib)
    set(TURRET_USD_INC_DIR /opt/Foundry/Katana6.0v1/external/FnUSD/include)

    set(TURRET_USD_LIBS
            fnarch
            fntf
            fnplug
            fnvt
            fnar
            )
    endif()

elseif(${USD_LIB_VARIANT} STREQUAL "MAYA")
    message("-- Building turret-usd for Maya USD libs")
    set(TURRET_USD_LIB_DIR $ENV{MAYA_USD_ROOT}/mayausd/USD/lib)
    set(TURRET_USD_INC_DIR $ENV{REZ_MAYA_ROOT}/include)
    if($ENV{REZ_MAYA_MAJOR_VERSION} GREATER 2023)
        set(TURRET_USD_LIBS
                usd_arch
                usd_tf
                usd_plug
                usd_vt
                usd_ar
                )
    else()
        set(TURRET_USD_LIBS
                arch
                tf
                plug
                vt
                ar
                )
    endif()
elseif(${USD_LIB_VARIANT} STREQUAL "BLENDER")
message("-- Building turret-usd for Blender Monolithic USD libs")
set(TURRET_USD_LIB_DIR $ENV{REZ_USD_MONOLITHIC_BLENDER_ROOT}/lib)
set(TURRET_USD_INC_DIR $ENV{REZ_USD_MONOLITHIC_BLENDER_ROOT}/include)
set(TURRET_USD_LIBS usd_ms )

elseif(${USD_LIB_VARIANT} STREQUAL "PXR")
if($ENV{REZ_USD_MAJOR_VERSION} GREATER_EQUAL 21)
message("-- Building turret-usd for Pixar USD libs")
set(TURRET_USD_LIB_DIR $ENV{REZ_USD_ROOT}/lib)
set(TURRET_USD_INC_DIR $ENV{REZ_USD_ROOT}/include)
set(TURRET_USD_LIBS
    usd_arch
    usd_tf
    usd_plug
    usd_vt
    usd_ar
)
else()
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
endif()

elseif(${USD_LIB_VARIANT} STREQUAL "PXR_MONOLITHIC")
message("-- Building turret-usd for monlithic Pixar USD libs")
set(TURRET_USD_LIB_DIR $ENV{REZ_USD_MONOLITHIC_ROOT}/lib)
set(TURRET_USD_INC_DIR $ENV{REZ_USD_MONOLITHIC_ROOT}/include)
set(TURRET_USD_LIBS usd_ms )

endif()

link_directories(
        ${TURRET_USD_LIB_DIR}
        $ENV{TBB_LIBRARIES}
)

include_directories(
        ${TURRET_INCLUDES}
        ${PC_LIBZMQ_INCLUDE_DIRS}
        ${CPPZMQ_INCLUDE_DIRS}
        ${PYTHON_INCLUDE_DIRS}
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
        $ENV{TBB_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}

    PUBLIC_HEADERS
        turretResolver.h

    CPPFILES
        turretResolver.cpp

    RESOURCE_FILES
        plugInfo.json
)

