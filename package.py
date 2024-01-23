# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.2.15'

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
    ['platform-linux', 'arch-x86_64', 'usd-19.11', 'tbb-2017.0', 'boost-1.55', '!katana', '!nuke'], # maya 2019
    ['platform-linux', 'arch-x86_64', 'houdini-18.0', 'devtoolset-6', 'boost-1.61', 'tbb-2019.0', '!katana', '!nuke'], # usd-19.11
    ['platform-linux', 'arch-x86_64', 'houdini-19.0', 'devtoolset-6', 'boost-1.72', 'tbb-2019.9', '!katana', '!nuke'], # usd-19.11
    ['platform-linux', 'arch-x86_64', 'boost_katana-1.70', 'katana-4.5.2', 'tbb_katana-2019.6', '!nuke', '!maya'], # usd_katana-21.05 katana 4.5
    # ['platform-linux', 'arch-x86_64', 'nuke-12.2.1', '!katana'], # usd-19.11

    ['platform-linux', 'arch-x86_64', 'usd-20.08', 'tbb-2017', 'boost-1.61', '!katana'],
    ['platform-linux', 'arch-x86_64', 'houdini-18.5', 'devtoolset-7', 'boost-1.72', 'tbb-2019.9', '!katana', '!nuke'], # usd-20.08
    ['platform-linux', 'arch-x86_64', 'usd-20.11', 'tbb-2017', 'boost-1.61', '!katana', '!nuke'], # usd-20.11, maya-2022
    ['platform-linux', 'arch-x86_64', 'usd-21.11', 'tbb-2020.3', 'boost-1.72', '!katana', '!nuke'], # usd-21.11, maya-2022
    ['platform-linux', 'arch-x86_64', 'tbb-2020.3', 'boost-1.76', 'maya-2023', '!katana', '!nuke', 'devtoolset-7'], # usd-21.11, maya-2023
    ['platform-linux', 'arch-x86_64', 'tbb-2018.4', 'boost-1.66', 'nuke-12', '!katana'], # usd-20.11, nuke-12.2v1

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
    
