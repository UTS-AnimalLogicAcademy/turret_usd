# -*- coding: utf-8 -*-

name = 'ala_usd_resolver'

version = '0.0.5'

requires = [
    'usd',
]

build_requires = [
    'cmake-3.2',
]

variants = [
	['platform-linux', 'arch-x86_64', 'usd-0.8.3'],
	['platform-linux', 'arch-x86_64', 'usd-0.8.4']
]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
