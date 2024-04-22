# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '2.4.1'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

requires = [
    'turret_lib-1.4+<2',
    'PyOpenGL-3.1.0',
    'jemalloc-4',
]

private_build_requires = [
    'cmake-3',
    'devtoolset-9'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80', 'usd-23.08', '!usd_monolithic', '!katana', '!nuke', '!maya', '!houdini', '!blender'], #usd-23.08 standalone
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80', 'usd_monolithic-23.08', '!usd', '!houdini', '!katana', '!maya', '!nuke'], #USD Monolithic 23.08 / Blender 3.6
    ['platform-linux', 'arch-x86_64', 'jinja-2', 'tbb-2020.3', 'boost-1.72', 'python-3.9', 'houdini-19.5.805', '!katana', '!nuke', '!maya', '!blender'], #houdini 19.5.640
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.72', 'python-3.10', 'houdini-20.0.653', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.0.590
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82', 'python-3.10', 'houdini-20.5.207', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.5.207 py3.10
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76', 'python-3.9', 'katana-6.0', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76', 'python-3.9', 'katana-6.5', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6.5
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.76', 'python-3.9', 'nuke-14.1', '!houdini', '!katana', '!maya', '!blender'], #Nuke 14.1
    

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
