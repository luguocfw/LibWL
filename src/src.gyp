#
#
# author: ChenFawang
# src.gyp
# 2019-1-19
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'libwl',
      'type': 'static_library',
      'include_dirs':[
        'include',
        '.',
      ],
      'sources':[
        'include/wl_memory.h',
        'include/wl_time.h',
        'include/wl_mutex.h',
        'include/wl_type.h',
        'include/wl_thread.h',
        'include/wl_dirent.h',
        'memory/wl_memory.c',
        'base/wl_list.c',
        'base/wl_list.h',
      ],
      'dependencies':[
        'os/<(WL_OS_NAME)/os.gyp:os_sources',
      ],
      'direct_dependent_settings':{
        'include_dirs':[
          'include',
        ],
      },
    },
  ], # targets
}