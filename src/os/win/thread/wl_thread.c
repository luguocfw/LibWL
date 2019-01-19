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

#include <process.h>
#include <windows.h>

struct WL_THREAD {
  HANDLE              thr_handle;
  unsigned            thr_id;
  void                *(*start_fun)(void *);
  void                *fun_arge;
  void                *re_data;
  char                *name;
  int                 name_len;
  WL_THREAD_ATTR      thr_attr;
};

typedef struct tagTHREADNAME_INFO
{
  DWORD     dwType; // must be 0x1000
  LPCSTR    szName; // pointer to name (in user addr space)
  DWORD     dwThreadID; // thread ID (-1=caller thread)
  DWORD     dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

void SetThreadName(DWORD dwThreadID, LPCSTR szThreadName)
{
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = szThreadName;
  info.dwThreadID = dwThreadID;
  info.dwFlags = 0;

  __try
  {
    RaiseException(0x406D1388, 0, sizeof(info) / sizeof(DWORD), (DWORD*)&info);
  }
  __except (EXCEPTION_CONTINUE_EXECUTION)
  {
  }
}

unsigned int __stdcall ThreadFun(PVOID pM) {
  struct WL_THREAD * thr_handle = (struct WL_THREAD *)pM;
  if (thr_handle->name != NULL || thr_handle->name_len > 0) {
    SetThreadName(thr_handle->thr_id, thr_handle->name);
  }
  thr_handle->re_data = thr_handle->start_fun(thr_handle->fun_arge);
  return 0;
}

int WLThreadCreate(WL_THREAD **thr, const WL_THREAD_ATTR *attr, const char *thread_name, void *(*fun)(void *), void *fun_arge) {
  int ret = WL_ERR_UNKNOW;
  struct WL_THREAD * thr_handle = NULL;
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
  thr_handle->thr_handle = (HANDLE)_beginthreadex(NULL, 0, ThreadFun, thr_handle, 0, &thr_handle->thr_id);
  if (thr_handle->thr_handle == NULL) {
    ret = WL_ERR_UNKNOW;
    goto err;
  }
  *thr = thr_handle;
  return 0;
err:
  if (thr_handle != NULL) {
    if (thr_handle->name != NULL) {
      free(thr_handle->name);
    }
    free(thr_handle);
  }
  return ret;
}

void WLThreadDestroy(WL_THREAD *thr, void **re_data) {
  if (thr == NULL) {
    return;
  }
  struct WL_THREAD *thr_handle = (struct WL_THREAD *)thr;
  WaitForSingleObject(thr_handle->thr_handle, INFINITE);
  if (re_data != NULL) {
    *re_data = thr_handle->re_data;
  }
  if (thr_handle->name != NULL) {
    WLFree(thr_handle->name);
  }
  WLFree(thr_handle);
}

void WLSleepMs(uint64_t ms)
{
  Sleep(ms);
}

void WLSleepSec(uint64_t sec)
{
  Sleep(sec * 1000);
}
