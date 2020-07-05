# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.1.10'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan' ]

requires = [
    'turret_lib-1.1.20+<2',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
    'jinja',
]

private_build_requires = [
    'cmake-3.2',
]

variants = [
	['platform-linux', 'arch-x86_64', 'usd-0.8.5', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-18.09', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-18.11', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-19.01', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-19.07', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-19.11', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd-20.02', 'tbb-4'],
	['platform-linux', 'arch-x86_64', 'usd_houdini_hdk', 'houdini-17', 'tbb-4'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.0', 'tbb-2019'],
    # ['platform-linux', 'arch-x86_64', 'houdini-18.5', 'tbb-2019'],
	['platform-linux', 'arch-x86_64', 'KatanaUsdPlugins-19.11.2', 'katana-3.5.2', 'tbb-4']
]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')