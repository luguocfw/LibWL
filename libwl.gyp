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
        '<(PRO_ROOT)',
      ],
      'conditions':[
        ['OS=="LINUX"',{
          'include_dirs':[
            '<(PRO_ROOT)/base/linux',
          ],
          'sources':[
            'base/linux/wl_log.c',
            'base/linux/wl_log.h',
          ],
        }],
        ['OS=="WIN32"',{
          'include_dirs':[
            '<(PRO_ROOT)/base/win',
          ],
          'sources':[
            'base/win/wl_log.c',
            'base/win/wl_log.h',
          ],
        }],
      ],
      'sources':[
      ],
    },
  ], # targets
}