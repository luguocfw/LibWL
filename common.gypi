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
        'configurations':{
          'Debug': {
            'msvs_settings':{
              'VCCLCompilerTool': {
                'RuntimeLibrary': '3',
                'Optimization':'0',
                'DebugInformationFormat':'4',
              },
              'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'GenerateMapFile': 'false',
                'SubSystem': '1',
              },
            },
          }, #Debug
          'Release': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'RuntimeLibrary': '2',
                'Optimization' : '2',
                'EnableIntrinsicFunctions':'true',
                'DebugInformationFormat': '3',
              },
              'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'GenerateMapFile': 'false',
              },
            }, #msvs_settings
          }, #Release
        }, #configurations
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