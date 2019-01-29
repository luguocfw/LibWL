#
#
# author: ChenFawang
# os.gyp
# 2019-1-29
# mail: cfwang_9984@163.com
#
{
  'targets':[
    {
      'target_name': 'os_sources',
      'type': 'none',
      'direct_dependent_settings':{
        'sources': [
          'thread/wl_mutex.c',
          'thread/wl_thread.c',
          'time/wl_time.c',
        ],
      },
    },
  ], # targets
}