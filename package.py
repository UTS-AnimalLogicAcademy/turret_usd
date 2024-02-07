# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '2.0.1'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

requires = [
    'turret_lib-1.2+<2',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
]

private_build_requires = [
    'cmake-3.12',
    'devtoolset-9'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80', 'usd-23.08', '!katana', '!nuke', '!maya', '!houdini'], #usd-23.08 standalone
    ['platform-linux', 'arch-x86_64', 'jinja-2', 'tbb-2020.3', 'boost-1.72', 'python-3.7', 'houdini-19.5.640', '!katana', '!nuke', '!maya'], #houdini 19.5.640
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.72', 'python-3.10', 'houdini-20.0.506', '!katana', '!nuke', '!maya'] #houdini 19.5.640

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
