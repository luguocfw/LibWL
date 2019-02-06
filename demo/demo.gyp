#
#
# author: ChenFawang
# demo.gyp
# 2019-1-19
# mail: cfwang_9984@163.com
#
{
  'includes': [
    './../common.gypi',
  ],
  'targets':[
    {
      'target_name': 'all_test',
      'type': 'executable',
      'sources':[
        'all_test.c',
      ],
      'dependencies': [
        '<(WL_ROOT)/src/src.gyp:libwl',
      ],
    },
  ], # targets
}