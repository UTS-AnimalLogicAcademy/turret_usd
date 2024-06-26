# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '2.4.3'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

requires = [
    'turret_lib-1.4+<2',
    'PyOpenGL-3.1.0',
    
]

private_build_requires = [
    'cmake-3.16',
    'devtoolset-9'
]

variants = [
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80', 'usd-23.08','jemalloc-4', '!usd_monolithic', '!mari', '!katana', '!nuke', '!maya', '!houdini', '!blender'], #usd-23.08 standalone
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80', 'usd_monolithic-23.08','jemalloc-4', '!usd', '!mari', '!houdini', '!katana', '!maya', '!nuke'], #USD Monolithic 23.08 / Blender 3.6
    ['platform-linux', 'arch-x86_64', 'jinja-2', 'tbb-2020.3', 'boost-1.72', 'python-3.9','jemalloc-4', 'houdini-19.5.805', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 19.5.640
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.72', 'python-3.10','jemalloc-5', 'houdini-20.0.653', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.0.590
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82', 'python-3.10','jemalloc-5', 'houdini-20.5.207', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.5.207 py3.10
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76','jemalloc-4', 'python-3.9', 'katana-6.0', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76','jemalloc-4', 'python-3.9', 'katana-6.5', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6.5
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.76','jemalloc-4', 'python-3.9', 'nuke-14.1', '!mari', '!houdini', '!katana', '!maya', '!blender'], #Nuke 14.1
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76', 'mari-6','jemalloc-4', 'python-3.9', '!nuke', '!houdini', '!katana', '!maya', '!blender'], #Mari 6
    

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
