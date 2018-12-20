set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE alaResolver)

link_directories($ENV{REZ_USD_ROOT}/lib $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/)

#include_directories($ENV{ZMQ_CLIENT_INCLUDE})
#link_libraries( $ENV{ZMQ_CLIENT_LIB}/libzmq_client_cpp.so )

find_package(Turret)
link_libraries(${TURRET_LIBRARY})
include_directories(${TURRET_INCLUDES})

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
        alaResolver.h

    CPPFILES
        alaResolver.cpp

    RESOURCE_FILES
        plugInfo.json
)
