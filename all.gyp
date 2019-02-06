#
#
# author: ChenFawang
# all.gyp
# 2019-1-19
# mail: cfwang_9984@163.com
#
{
  'includes': [
    'common.gypi',
  ],
  'targets':[
    {
      'target_name': 'wl_all',
      'type': 'none',
      'dependencies':[
        'src/src.gyp:*',
        'demo/demo.gyp:*',
      ],
    }, # 'target_name': 'wl_all',
  ], # targets
}