# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.3.1'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan' ]

requires = [
    'turret_lib-1.2+<2',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
    'jinja',
]

private_build_requires = [
    'cmake-3.12',
]

variants = [
    # ['platform-linux', 'arch-x86_64', 'usd-19.11', 'tbb-4.4', 'boost-1.55', '!katana'],
    ['platform-linux', 'arch-x86_64', 'usd-19.11', 'tbb-2017.0', 'boost-1.55', '!katana'], # maya 2019
    ['platform-linux', 'arch-x86_64', 'houdini-18.0', 'devtoolset-6', 'boost-1.61', 'tbb-2019.0', '!katana'], # usd-19.11
    ['platform-linux', 'arch-x86_64', 'KatanaUsdPlugins-19.11.3.1', 'katana-3.6.2', 'tbb_katana'], # usd-19.11
    # ['platform-linux', 'arch-x86_64', 'nuke-12.2.1', '!katana'], # usd-19.11

    ['platform-linux', 'arch-x86_64', 'usd-20.08', 'tbb-2017', 'boost-1.61', '!katana'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.5', 'devtoolset-6', 'boost-1.72', 'tbb-2019.9', '!katana'], # usd-20.08

]

def commands():
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    
