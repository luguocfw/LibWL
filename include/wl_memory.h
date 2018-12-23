//
//
// Copyright 
// author: ChenFawang
// wl_memory.h
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#ifndef __WL_MEMORY_H__
#define __WL_MEMORY_H__
#include <stdlib.h>

void *WLMalloc(long size);

void WLFree(void *ptr);

#endif