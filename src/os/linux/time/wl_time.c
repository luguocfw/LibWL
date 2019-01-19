//
//
// Copyright 
// author: ChenFawang
// wl_time.c
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#include <wl_time.h>
#include <sys/time.h>

int64_t WLGetTimeSec() {
  return (int64_t)time(NULL);
}

int64_t WLGetTimeMs() {
  struct timeval time; 
  gettimeofday(&time, NULL); 
  return (int64_t)((int64_t)(time.tv_sec * 1000) + (int64_t)(time.tv_usec / 1000));
}

int64_t WLGetTimeUs() {
  struct timeval time;
  gettimeofday(&time, NULL);
  return (int64_t)((int64_t)(time.tv_sec * 1000000) + (int64_t)time.tv_usec);
}