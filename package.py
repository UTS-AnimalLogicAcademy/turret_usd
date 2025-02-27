# -*- coding: utf-8 -*-

name = 'turret_usd'

version = '2.6.10'

authors = [ 'ben.skinner',
            'daniel.flood',
            'wen.tan',
	    'jonah.newton' ]

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
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.1', 'usd-25.02','jemalloc-4', '!usd_monolithic', '!mari', '!katana', '!nuke', '!maya', '!houdini', '!blender'], #usd-25.02 standalone
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.1', 'usd_monolithic_blender-24.05','jemalloc-4', 'blender-4.2', '!usd', '!mari', '!houdini', '!katana', '!maya', '!nuke'], #Blender 4.2
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.1', 'usd_monolithic_blender-24.05','jemalloc-4', 'blender-4.3', '!usd', '!mari', '!houdini', '!katana', '!maya', '!nuke'], #Blender 4.2
    ['platform-linux', 'arch-x86_64', 'jinja-2', 'tbb-2020.3', 'boost-1.72', 'python-3.9', 'houdini-19.5.805', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 19.5.640
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.72', 'python-3.10', 'houdini-20.0.751', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.0.590
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.2', 'python-3.10', 'houdini-20.5.445', '!mari', '!katana', '!nuke', '!maya', '!blender'], #houdini 20.5.445 py3.10
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76','jemalloc-4', 'python-3.9', 'katana-6.0', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.80', 'jemalloc-4', 'python-3.10', 'katana-7.0', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 7
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.82', 'jemalloc-4', 'python-3.11', 'katana-8.0', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 8
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76','jemalloc-4', 'python-3.9', 'katana-6.5', '!mari', '!houdini', '!nuke', '!maya', '!blender'], #Katana 6.5
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.76','jemalloc-4', 'python-3.9', 'nuke-14.1', '!mari', '!houdini', '!katana', '!maya', '!blender'], #Nuke 14.1
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.80','jemalloc-4', 'python-3.10', 'nuke-15.1', '!mari', '!houdini', '!katana', '!maya', '!blender','!usd'], #Nuke 15.1
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.76', 'mari-6','jemalloc-4', 'python-3.9', '!nuke', '!houdini', '!katana', '!maya', '!blender'], #Mari 6
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb_katana-2020.3', 'boost_katana-1.80', 'mari-7','jemalloc-4', 'python-3.10', '!nuke', '!houdini', '!katana', '!maya', '!blender'], #Mari 7
    ['platform-linux', 'arch-x86_64', 'jinja-3', 'tbb-2020.3', 'boost-1.82.0.1', 'maya-2025','jemalloc-4', 'python-3.11', '!nuke', '!houdini', '!katana', '!mari', '!blender'], #Maya 2025
    

]

def commands():
    env.LD_LIBRARY_PATH.append('{root}/plugin/usd')
    env.KATANA_RESOURCES.append('{root}/plugin')
    env.PXR_PLUGINPATH_NAME.append('{root}/plugin/usd/')
    env.FNPXR_PLUGINPATH.append('{root}/plugin/usd/')
    
    # We do not seem to see much benefit beyond 12 threads with the multiprocessed turret server, 
    # and uncapping actually hinders performance due to CPU throttling.
    env.PXR_WORK_THREAD_LIMIT.set(12)
