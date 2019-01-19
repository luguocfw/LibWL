//
//
// Copyright 
// author: ChenFawang
// wl_thread.c
// 2018 - 12 - 25
// mail: cfwang_9984@163.com
//
#include <wl_thread.h>
#include <wl_memory.h>
#include <wl_type.h>

#include <pthread.h>
#include <sys/prctl.h>
#include <unistd.h>

struct WL_THREAD {
  pthread_t         thread_id;
  void              *(*start_fun)(void *);
  void              *fun_arge;
  char              *name;
  int               name_len;
  WL_THREAD_ATTR    thread_attr;
};

static void *WLThreadFirstCall(void *arge) {
  struct WL_THREAD *thr_handle = (struct WL_THREAD *)arge;
  if (thr_handle->name != NULL && thr_handle->name_len > 0) {
    prctl(PR_SET_NAME, thr_handle->name);
  }
  return thr_handle->start_fun(thr_handle->fun_arge);
}

int WLThreadCreate(WL_THREAD ** thr, const WL_THREAD_ATTR * attr, const char * thread_name, void *(*fun)(void *), void * fun_arge)
{
  int ret = WL_ERR_UNKNOW;
  struct WL_THREAD *thr_handle = NULL;
  if (fun == NULL) {
    ret = WL_ERR_NULLPTR;
    goto err;
  }
  thr_handle = (struct WL_THREAD *)WLMalloc(sizeof(struct WL_THREAD));
  if (thr_handle == NULL) {
    ret = WL_ERR_NOMEM;
    goto err;
  }
  thr_handle->start_fun = fun;
  thr_handle->fun_arge = fun_arge;
  if (thread_name == NULL || strlen(thread_name) == 0) {
    thr_handle->name = NULL;
    thr_handle->name_len = 0;
  }
  else {
    thr_handle->name_len = strlen(thread_name) + 1;
    thr_handle->name = (char *)WLMalloc(thr_handle->name_len);
    if (thr_handle->name == NULL) {
      ret = WL_ERR_NOMEM;
      goto err;
    }
    memset(thr_handle->name, 0, thr_handle->name_len);
    strcpy(thr_handle->name, thread_name);
  }
  ret = pthread_create(&thr_handle->thread_id, NULL, WLThreadFirstCall, thr_handle);
  if (ret != 0) {
    ret = WL_ERR_UNKNOW;
    goto err;
  }
  *thr = thr_handle;
  return 0;
err:
  if (thr_handle != NULL) {
    if (thr_handle->name != NULL) {
      WLFree(thr_handle->name);
    }
    WLFree(thr_handle);
  }
  return ret;
}

void WLThreadDestroy(WL_THREAD * thr, void ** re_data)
{
  if (thr == NULL) {
    return;
  }
  struct WL_THREAD * thr_handle = (struct WL_THREAD)thr;
  pthread_join(thr_handle->thread_id, re_data);
  if (thr_handle->name != NULL) {
    WLFree(thr_handle->name);
  }
  WLFree(thr_handle);
}

void WLSleepMs(uint64_t ms)
{
  usleep(ms * 1000);
}

void WLSleepSec(uint64_t sec)
{
  sleep(sec);
}
