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
        '<(PRO_ROOT)/src/include',
        '.',
      ],
      'sources':[
        'include/wl_memory.h',
        'include/wl_time.h',
        'include/wl_mutex.h',
        'include/wl_type.h',
        'include/wl_thread.h',
        'memory/wl_memory.c',
#        'os/<(os_name)/thread/wl_mutex.c',
#        'os/<(os_name)/thread/wl_thread.c',
#        'os/<(os_name)/time/wl_time.c',
      ],
      'dependencies':[
        'os/<(os_name)/os.gyp:os_sources',
      ],
      'direct_dependent_settings':{
        'include_dirs':[
          '<(PRO_ROOT)/src/include',
        ],
      },
    },
  ], # targets
}