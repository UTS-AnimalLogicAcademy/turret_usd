set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE alaResolver)

include_directories($ENV{ZMQ_CLIENT_INCLUDE})

link_directories($ENV{REZ_USD_ROOT}/lib $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/)

link_libraries( $ENV{ZMQ_CLIENT_LIB}/libzmq_client_cpp.so )

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
