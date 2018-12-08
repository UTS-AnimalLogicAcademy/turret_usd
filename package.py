# -*- coding: utf-8 -*-

name = 'ala_usd_resolver'

version = '0.0.25'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan' ]

requires = [
    'usd',
    'zmq_client_cpp-0.0.8+',
    'PyOpenGL-3.1.0'
]

build_requires = [
    'cmake-3.2',
]

variants = [
	['platform-linux', 'arch-x86_64', 'usd-0.8.3'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.4'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.5'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.6.001'],
	['platform-linux', 'arch-x86_64', 'usd-18.09'],
	['platform-linux', 'arch-x86_64', 'usd-18.11'],
	['platform-linux', 'arch-x86_64', 'usd-19.01']
]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.ALA_USD_RESOLVER_LOG_LEVEL.set("1")

    env.ZMQ_CACHE_QUERIES.set("1")
    #env.PXR_WORK_THREAD_LIMIT.set(1)
