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

#include <Windows.h>

struct WL_MUTEX {
  HANDLE      win_mutex;
};

int WLMutexCreate(WL_MUTEX **mutex, WL_MUTEX_TYPE type) {
  struct WL_MUTEX *new_mutex = WLMalloc(sizeof(struct WL_MUTEX));
  if (new_mutex == NULL) {
    return WL_ERR_NOMEM;
  }
  new_mutex->win_mutex = CreateMutex(NULL, FALSE, NULL);
  if (new_mutex->win_mutex == NULL) {
    return WL_ERR_UNKNOW;
  }
  *mutex = new_mutex;
  return WL_SUCCESS;
}

void WLMutexDestroy(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return;
  }
  CloseHandle(mutex->win_mutex);
  WLFree(mutex);
}

int WLMutexLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  DWORD ret = WaitForSingleObject(mutex->win_mutex, INFINITE);
  if (ret != WAIT_OBJECT_0) {
    return WL_ERR_UNKNOW;
  }
  return WL_SUCCESS;
}

int WLMutexUnLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  ReleaseMutex(mutex->win_mutex);
  return WL_SUCCESS;
}

WL_MUTEX_TRY_RE WLMutexTryLock(WL_MUTEX *mutex) {
  if (mutex == NULL) {
    return WL_ERR_NULLPTR;
  }
  DWORD ret = WaitForSingleObject(mutex->win_mutex, 0);
  if (ret != WAIT_OBJECT_0) {
    return WL_MUTEX_BUSY;
  }
  return WL_MUTEX_LOCK;
}