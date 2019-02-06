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
      ['WL_OS=="LINUX"',{
        'defines': ['WL_OS_LINUX'],
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
          ['wl_build_type=="debug"',{
            'cflags':[
              '-g',
            ],
          }], # wl_build_type=="debug"
        ], # conditions
      }], # WL_OS=="LINUX"
      ['WL_OS=="WIN32"',{
        'defines': ['WL_OS_WIN32'],
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
      }], # WL_OS="WIN32"
      ['wl_build_type=="debug"',{
        'defines': ['WL_BUILD_DEBUG'],
      }],
      ['wl_build_type=="release"',{
        'defines': ['WL_BUILD_RELEASE'],
      }],
	], # conditions
  },
}