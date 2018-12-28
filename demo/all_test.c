//
//
// Copyright 
// author: ChenFawang
// all_test.h=c
// 2018 - 12 - 28
// mail: cfwang_9984@163.com
//
#include <stdio.h>
#include <string.h>
#include <wl_memory.h>
#include <wl_mutex.h>
#include <wl_thread.h>
#include <wl_time.h>
#include <wl_type.h>

static char *g_buf_ = NULL;
static int g_buf_len_ = 0;
static WL_MUTEX *g_data_mutex_ = NULL;
static int g_thr0_run_ = 0;
static int g_thr1_run_ = 0;
static int g_thr2_run_ = 0;
static WL_THREAD *g_thread20_ = NULL;
static int g_thr20_run_ = 0;

static void *Thread0(void *arge) {
  char *test_str = (char *)arge;
  while (g_thr0_run_ == 1) {
    printf("thread 0 wait lock...\n");
    WLMutexLock(g_data_mutex_);
    printf("thread 0 get lock!!\n");
    if (g_buf_ != NULL) {
      printf("thread 0 old g_buf is:%s,modify to %s\n", g_buf_, test_str);
      memset(g_buf_, 0, g_buf_len_);
      strcpy(g_buf_, test_str);
    }
    else
    {
      printf("thread 0 old g_buf is NULL\n");
    }
    printf("thread 0 sleep ...\n");
    WLSleepMs(10);
    WLSleepSec(1);
    WLMutexUnLock(g_data_mutex_);
    printf("thread 0 release lock\n");
  }
  printf("thread 0 exit...\n");
  return NULL;
}

static void *Thread1(void *arge) {
  char *test_str = (char *)arge;
  while (g_thr1_run_ == 1) {
    printf("thread 1 wait lock...\n");
    WLMutexLock(g_data_mutex_);
    printf("thread 1 get lock!!\n");
    if (g_buf_ != NULL) {
      printf("thread 1 old g_buf is:%s,modify to %s\n", g_buf_, test_str);
      memset(g_buf_, 0, g_buf_len_);
      strcpy(g_buf_, test_str);
    }
    else
    {
      printf("thread 1 old g_buf is NULL\n");
    }
    printf("thread 1 sleep ...\n");
    WLSleepMs(10);
    WLSleepSec(1);
    WLMutexUnLock(g_data_mutex_);
    printf("thread 1 release lock\n");
  }
  printf("thread 1 exit...\n");
  return NULL;
}

static void *Thread20(void *arge) {
  char test_str[] = "test thread 2.0";
  while (g_thr20_run_ == 1) {
    printf("thread 2.0 wait lock...\n");
    WLMutexLock(g_data_mutex_);
    printf("thread 2.0 get lock!!\n");
    if (g_buf_ != NULL) {
      printf("thread 2.0 old g_buf is:%s,modify to %s\n", g_buf_, test_str);
      memset(g_buf_, 0, g_buf_len_);
      strcpy(g_buf_, test_str);
    }
    else
    {
      printf("thread 2.0 old g_buf is NULL\n");
    }
    printf("thread 2.0 sleep ...\n");
    WLSleepMs(10);
    WLSleepSec(1);
    WLMutexUnLock(g_data_mutex_);
    printf("thread 2.0 release lock\n");
  }
  printf("thread 2.0 exit...\n");
  return NULL;
}

static void *Thread2(void *arge) {
  char *test_str = (char *)arge;
  g_thr20_run_ = 1;
  int ret = WLThreadCreate(&g_thread20_, NULL, "test_thread_20", Thread20, NULL);
  if (ret != 0) {
    printf("create sub thread failed\n");
  }
  while (g_thr2_run_ == 1) {
    printf("thread 2 wait lock...\n");
    WLMutexLock(g_data_mutex_);
    printf("thread 2 get lock!!\n");
    if (g_buf_ != NULL) {
      printf("thread 2 old g_buf is:%s,modify to %s\n", g_buf_, test_str);
      memset(g_buf_, 0, g_buf_len_);
      strcpy(g_buf_, test_str);
    }
    else
    {
      printf("thread 2 old g_buf is NULL\n");
    }
    printf("thread 2 sleep ...\n");
    WLSleepMs(10);
    WLSleepSec(1);
    WLMutexUnLock(g_data_mutex_);
    printf("thread 2 release lock\n");
    break;
  }
  printf("thread 2 exit...\n");
  return NULL;
}

int main() {
#if defined(OS_WIN32)
  //_CrtSetBreakAlloc(81);
#endif
  WL_THREAD  *threads_fd[3] = { NULL };
  int thread_cnt = 3;
  g_buf_len_ = 256;
  g_buf_ = (char *)WLMalloc(g_buf_len_);
  if (g_buf_ == NULL) {
    printf("malloc failed!!\n");
    goto err;
  }
  memset(g_buf_, 0, g_buf_len_);
  int ret = WLMutexCreate(&g_data_mutex_, WL_MUTEX_DEFAULT);
  if (ret != 0) {
    printf("create mutex failed\n");
    goto err;
  }
  g_thr0_run_ = 1;
  ret = WLThreadCreate(&threads_fd[0], NULL, "test_thread_0", Thread0, "thread 0 test string!!");
  if (ret != 0) {
    printf("create thread 0 failed\n");
    goto err;
  }
  g_thr1_run_ = 1;
  ret = WLThreadCreate(&threads_fd[1], NULL, "test_thread_1", Thread1, "thread 1 test string!!");
  if (ret != 0) {
    printf("create thread 1 failed\n");
    goto err;
  }
  g_thr2_run_ = 1;
  ret = WLThreadCreate(&threads_fd[2], NULL, "test_thread_2", Thread2, "thread 2 test string!!");
  if (ret != 0) {
    printf("create thread 2 failed\n");
    goto err;
  }
  WLSleepSec(10);
  g_thr2_run_ = 0;
  WLThreadDestroy(threads_fd[2], NULL);
  g_thr20_run_ = 0;
  WLThreadDestroy(g_thread20_, NULL);
  g_thr1_run_ = 0;
  WLThreadDestroy(threads_fd[1], NULL);
  g_thr0_run_ = 0;
  WLThreadDestroy(threads_fd[0], NULL);
  WLMutexDestroy(g_data_mutex_);
  WLFree(g_buf_);
#if defined(OS_WIN32)
  _CrtDumpMemoryLeaks();
#endif
  return 0;
err:
  if (threads_fd[2] != NULL) {
    g_thr2_run_ = 0;
    WLThreadDestroy(threads_fd[2],NULL);
  }
  if (threads_fd[1] != NULL) {
    g_thr1_run_ = 0;
    WLThreadDestroy(threads_fd[1],NULL);
  }
  if (threads_fd[0] != NULL) {
    g_thr0_run_ = 0;
    WLThreadDestroy(threads_fd[0],NULL);
  }
  if (g_data_mutex_ != NULL) {
    WLMutexDestroy(g_data_mutex_);
  }
  if (g_buf_ != 0) {
    WLFree(g_buf_);
  }
#if defined(OS_WIN32)
  _CrtDumpMemoryLeaks();
#endif
  return 1;
}