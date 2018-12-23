#
#
# author: ChenFawang
# common.gypi
# 2018-12-23
# mail: cfwang_9984@163.com
#
{
  'target_defaults': {
    'conditions': [
      ['OS=="LINUX"',{
        'defines': ['OS_LINUX'],
        'libraries': [
          '-lpthread',
          '-lrt',
          '-lm',
          '-ldl',
        ],
        'cflags':[
          '-fPIC',
        ],
        'conditions': [
          ['build_type=="debug"',{
            'cflags':[
              '-g',
            ],
          }], # build_type=="debug"
        ], # conditions
      }], # OS=="LINUX"
	  ['OS=="WIN32"',{
        'defines': ['OS_WIN32'],
      }], # OS="WIN32"
      ['build_type=="debug"',{
        'defines': ['BUILD_DEBUG'],
      }],
      ['build_type=="release"',{
        'defines': ['BUILD_RELEASE'],
      }],
	], # conditions
  },
}