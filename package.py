# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.1.4'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan' ]

requires = [
    'turret_lib-1.1.11+<2',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
    'jinja',
    'tbb'
]

private_build_requires = [
    'cmake-3.2',
]

variants = [
	['platform-linux', 'arch-x86_64', 'usd-0.8.5'],
	['platform-linux', 'arch-x86_64', 'usd-18.09'],
	['platform-linux', 'arch-x86_64', 'usd-18.11'],
	['platform-linux', 'arch-x86_64', 'usd-19.01'],
	['platform-linux', 'arch-x86_64', 'usd-19.07'],
	['platform-linux', 'arch-x86_64', 'usd_houdini_hdk', 'houdini-17'],
	['platform-linux', 'arch-x86_64', 'usd_houdini_hdk', 'houdini-18']
]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')


