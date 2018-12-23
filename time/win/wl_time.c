//
//
// Copyright 
// author: ChenFawang
// wl_time.c
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#include <wl_time.h>
#include <Windows.h>
#include <sys/timeb.h>


int64_t GetTimeSec() {
  return (int64_t)time(NULL);
}

int64_t GetTimeMs() {
  struct timeb rawtime;
  ftime(&rawtime);
  return (int64_t)((int64_t)rawtime.time * 1000 + (int64_t)rawtime.millitm);
}

int64_t GetTimeUs() {
  return GetTimeMs() * 1000;
}