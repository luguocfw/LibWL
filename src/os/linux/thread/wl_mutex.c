//
//
// Copyright 
// author: ChenFawang
// wl_mutex.c
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#include <wl_mutex.h>
#include <wl_type.h>
#include <wl_memory.h>

#include <pthread.h>

struct WL_MUTEX {
  pthread_mutex_t     linux_mutex;
};

int WLMutexCreate(WL_MUTEX **mutex, WL_MUTEX_TYPE type) {
  struct WL_MUTEX *new_mutex = WLMalloc(sizeof(struct WL_MUTEX));
  if (new_mutex == NULL) {
    return WL_ERR_NOMEM;
  }
  int ret = pthread_mutex_init(&new_mutex->linux_mutex, NULL);
  if (ret != 0) {
    WLFree(new_mutex);
    return WL_ERR_UNKNOW;
  }
  *mutex = new_mutex;
  return WL_SUCCESS;
}

void WLMutexDestroy(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return;
  }
  pthread_mutex_destroy(&mutex->linux_mutex);
  WLFree(mutex);
}

int WLMutexLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  int ret = pthread_mutex_lock(&mutex->linux_mutex);
  if (ret != 0) {
    return WL_ERR_UNKNOW;
  }
  return WL_SUCCESS;
}

int WLMutexUnLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  int ret = pthread_mutex_unlock(&mutex->linux_mutex);
  if (ret != 0) {
    return WL_ERR_UNKNOW;
  }
  return WL_SUCCESS;
}

WL_MUTEX_TRY_RE WLMutexTryLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  int ret = pthread_mutex_trylock(&mutex->linux_mutex);
  if (ret != 0) {
    return WL_MUTEX_BUSY;
  }
  return WL_MUTEX_LOCK;
}