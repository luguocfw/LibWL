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
          ],
        }],
        ['OS=="WIN32"',{
          'sources':[
            'time/win/wl_time.c',
          ],
        }],
      ],
      'sources':[
        'include/wl_time.h'
      ],
    },
  ], # targets
}