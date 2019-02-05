# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '0.0.2'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan' ]

requires = [
    'turret_lib',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
    'jinja',
    'tbb'
]

private_build_requires = [
    'cmake-3.2',
]

variants = [
	['platform-linux', 'arch-x86_64', 'usd-0.8.3'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.4'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.5'],
	['platform-linux', 'arch-x86_64', 'usd-18.09'],
	['platform-linux', 'arch-x86_64', 'usd-18.11'],
	['platform-linux', 'arch-x86_64', 'usd-19.01'],
	['platform-linux', 'arch-x86_64', 'usd_houdini_hdk-17.0'],
	['platform-linux', 'arch-x86_64', 'usd_houdini_hdk-17.5']
]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')


