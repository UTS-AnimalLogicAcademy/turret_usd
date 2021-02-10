# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.2.1'

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
    ['platform-linux', 'arch-x86_64', 'usd-19.01', 'tbb-4.4', 'boost-1.55'],
    ['platform-linux', 'arch-x86_64', 'usd-19.07', 'tbb-4.4', 'boost-1.55'],
    ['platform-linux', 'arch-x86_64', 'usd-19.11', 'tbb-4.4', 'boost-1.55'],
    ['platform-linux', 'arch-x86_64', 'usd-20.02', 'tbb-4.4', 'boost-1.55'],
    ['platform-linux', 'arch-x86_64', 'usd-20.05', 'tbb-2017', 'boost-1.61'],
    ['platform-linux', 'arch-x86_64', 'usd-20.08', 'tbb-2017', 'boost-1.61'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.0', 'devtoolset-6', 'tbb-4.4', 'boost-1.55'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.5.351', 'devtoolset-6', 'boost-1.61', 'tbb-2017'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.5.462', 'devtoolset-6', 'boost-1.61', 'tbb-2017'],
   # ['platform-linux', 'arch-x86_64', 'nuke-12.2.1', '!katana'],
    ['platform-linux', 'arch-x86_64', 'KatanaUsdPlugins-19.11.3.1', 'katana-3.6.2', 'tbb_katana']
]

def commands():
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    
