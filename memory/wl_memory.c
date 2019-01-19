//
//
// Copyright 
// author: ChenFawang
// wl_memory.c
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#include <wl_memory.h>
#include <stdlib.h>


void *WLMalloc(long size) {
  return malloc(size);
}

void WLFree(void *ptr) {
  if (ptr == NULL) {
    return;
  }
  free(ptr);
}
