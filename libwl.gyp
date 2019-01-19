#
#
# author: ChenFawang
# all.gyp
# 2018-12-23
# mail: cfwang_9984@163.com
#
{
  'includes': [
    'common.gypi',
  ],
  'targets':[
    {
      'target_name': 'libwl',
      'type': 'static_library',
      'include_dirs':[
        '<(PRO_ROOT)/include',
      ],
      'conditions':[
        ['OS=="LINUX"',{
          'sources':[
            'time/linux/wl_time.c',
            'thread/linux/wl_mutex.c',
            'thread/linux/wl_thread.c',
          ],
        }],
        ['OS=="WIN32"',{
          'sources':[
            'time/win/wl_time.c',
            'thread/win/wl_mutex.c',
            'thread/win/wl_thread.c',
          ],
        }],
      ],
      'sources':[
        'memory/wl_memory.c',
        'include/wl_memory.h',
        'include/wl_time.h',
        'include/wl_mutex.h',
        'include/wl_type.h',
        'include/wl_thread.h',
      ],
      'direct_dependent_settings':{
        'include_dirs':[
          '<(PRO_ROOT)/include',
        ],
      },
    },
    {
      'target_name': 'thread_test',
      'type': 'executable',
      'sources':[
        'demo/all_test.c',
      ],
      'dependencies': [
        'libwl',
      ],
    },
  ], # targets
}