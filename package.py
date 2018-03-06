# -*- coding: utf-8 -*-

name = 'ala_usd_resolver'

version = '0.0.2'

requires = [
    'usd',
]

build_requires = [
    'cmake-3.2',
]

variants = [['platform-linux', 'arch-x86_64']]

def commands():
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
