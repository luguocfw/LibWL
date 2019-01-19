//
//
// Copyright 
// author: ChenFawang
// wl_mutex.h
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#ifndef __WL_MUTEX_H__
#define __WL_MUTEX_H__

typedef struct WL_MUTEX WL_MUTEX;

typedef enum {
  WL_MUTEX_DEFAULT = 0,
}WL_MUTEX_TYPE;

typedef enum {
  WL_MUTEX_BUSY = 1,
  WL_MUTEX_LOCK = 2,
}WL_MUTEX_TRY_RE;

int WLMutexCreate(WL_MUTEX **mutex, WL_MUTEX_TYPE type);

void WLMutexDestroy(WL_MUTEX *mutex);

int WLMutexLock(WL_MUTEX *mutex);

int WLMutexUnLock(WL_MUTEX *mutex);

WL_MUTEX_TRY_RE WLMutexTryLock(WL_MUTEX *mutex);



#endif