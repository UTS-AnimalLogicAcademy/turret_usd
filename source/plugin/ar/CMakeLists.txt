set(PXR_PREFIX pxr/usd)
set(PXR_PACKAGE alaResolver)

link_directories($ENV{REZ_USD_ROOT}/lib $ENV{REZ_TBB_ROOT}/lib/intel64/gcc4.4/)

pxr_plugin(${PXR_PACKAGE}
    LIBRARIES
        arch
        tf
        plug
        vt
        ar
        ${Boost_PYTHON_LIBRARY}
        $ENV{ZMQ_CLIENT_LIB}

    INCLUDE_DIRS
        $ENV{REZ_USD_ROOT}/include
        $ENV{REZ_TBB_ROOT}/include
        ${Boost_INCLUDE_DIRS}
        $ENV{ZMQ_CLIENT_INCLUDE}

    PUBLIC_HEADERS
        alaResolver.h

    CPPFILES
        #zmqDispatch.cpp
        alaResolver.cpp

    RESOURCE_FILES
        plugInfo.json
)