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
#include <wl_dirent.h>

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

static int ThreadAndMutexTest() {
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
  return 0;
err:
  if (threads_fd[2] != NULL) {
    g_thr2_run_ = 0;
    WLThreadDestroy(threads_fd[2], NULL);
  }
  if (threads_fd[1] != NULL) {
    g_thr1_run_ = 0;
    WLThreadDestroy(threads_fd[1], NULL);
  }
  if (threads_fd[0] != NULL) {
    g_thr0_run_ = 0;
    WLThreadDestroy(threads_fd[0], NULL);
  }
  if (g_data_mutex_ != NULL) {
    WLMutexDestroy(g_data_mutex_);
  }
  if (g_buf_ != 0) {
    WLFree(g_buf_);
  }
  return 1;
}

static long TraversDir(WL_DIR *dir) {
  long total_offset = 0;
  WL_DIRENT *ent = NULL;
  while (1) {
    total_offset = WLTelldir(dir);
    printf("dir tell :%ld\n", total_offset);
    ent = WLReaddir(dir);
    if (ent == NULL) {
      break;
    }
    printf("find dir:\tname:%s size:%d type:", ent->name, ent->size);
    switch (ent->type) {
      case WL_DIR_DIR:printf("SUBDIR\n"); break;
      case WL_DIR_FILE:printf("FILE\n"); break;
      case WL_DIR_UNKNOW:printf("UNKNOW\n"); break;
      default:printf("ERROR\n"); break;
    }
  }
  return total_offset;
}

static int DirentTest() {
#if defined(WL_OS_WIN32)
  char test_dir[] = "E:\\test_dir";
#elif defined(WL_OS_LINUX)
  char test_dir[] = "/";
#endif
  printf(">>>>>>>>dirent test<<<<<<<<<<<\n");
  printf("test dir: %s\n", test_dir);
  printf("system dir interval:%c\n", WLDirInterval());
  WL_DIR *dir = WLOpenDir(test_dir);
  if (dir == NULL) {
    printf("open dir:%s failed\n", test_dir);
    return 1;
  }
  TraversDir(dir);
  printf("rewind dir test....\n");
  WLRewindDir(dir);
  int max_offset = TraversDir(dir);
  if (max_offset > 0) {
    printf("seek dir test, dir seek:%ld\n", max_offset / 2);
    WLSeekDir(dir, max_offset / 2);
    TraversDir(dir);
  }
  printf("close dir handle...\n");
  WLCloseDir(dir);
  printf("dirent test over , input enykey to continue\n");
  getchar();
  return 0;
}

void Usage() {
  printf("all_test <test_num>\n");
  printf("\t\ttest_num:\n");
  printf("\t\t\t0: thread and mutex test\n");
  printf("\t\t\t1: dirent traversing test\n");
}

int main(int argc, char *argv[]) {
#if defined(WL_OS_WIN32)
  //_CrtSetBreakAlloc(81);
#endif
  if (argc != 2) {
    Usage();
    goto exit;
  }
  switch (atoi(argv[1])) {
    case 0:
      ThreadAndMutexTest();
      break;
    case 1:
      DirentTest();
      break;
    default:
      Usage();
      break;
  }
exit:
#if defined(WL_OS_WIN32)
  _CrtDumpMemoryLeaks();
#endif
  return 0;
}