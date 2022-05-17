# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.2.11'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

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
    ['platform-linux', 'arch-x86_64', 'houdini-19.0', 'devtoolset-6', 'boost-1.72', 'tbb-2019.9', '!katana'], # usd-19.11
    ['platform-linux', 'arch-x86_64', 'usd-21.05', 'boost-1.70', 'katana-4.5.2', 'tbb_katana-2019.6'], # usd-21.05 katana 4.5
    # ['platform-linux', 'arch-x86_64', 'nuke-12.2.1', '!katana'], # usd-19.11

    ['platform-linux', 'arch-x86_64', 'usd-20.08', 'tbb-2017', 'boost-1.61', '!katana'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.5', 'devtoolset-7', 'boost-1.72', 'tbb-2019.9', '!katana'], # usd-20.08
    ['platform-linux', 'arch-x86_64', 'usd-20.11', 'tbb-2017', 'boost-1.61', '!katana'], # usd-20.11, maya-2022

]

def commands():
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    
