# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '2.8.0'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton',
        'anthony.pomes' ]

requires = [
    'turret_lib-1.4+<2',
    'PyOpenGL',
    'os-RedHatEnterprise-9+'
    
]

private_build_requires = [
    'cmake-3.16',
    'devtoolset-9+'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.2', 'maya-2025','jemalloc-4', 'python-3.10', '!nuke', '!houdini', '!katana', '!mari', '!blender'], #Maya 2025

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
    
    env.DEFAULT_USD.set('{root}/resources/DefaultUSD.usda')
    env.TURRET_USD_SUPPRESS_ASSET_NOT_FOUND.set('1')
    env.TURRET_DO_LOG.set('0')
