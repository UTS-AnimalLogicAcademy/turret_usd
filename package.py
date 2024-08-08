# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '1.2.17'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

requires = [
    'turret_lib-1.2+<2',
    'PyOpenGL',
    'jemalloc-4',
    'jinja-2',
    'os-RedHatEnterprise-8+'
]

private_build_requires = [
    'cmake-3.12',
    'devtoolset-7+', 
]

variants = [
    ['platform-linux', 'arch-x86_64', 'tbb-2020.3', 'boost-1.76', 'maya-2023', '!katana', '!nuke'], # usd-21.11, maya-2023

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
    
