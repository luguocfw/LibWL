//
//
// Copyright 
// author: ChenFawang
// wl_thread.h
// 2018 - 12 - 25
// mail: cfwang_9984@163.com
//
#ifndef __WL_THREAD_H__
#define __WL_THREAD_H__

typedef struct WL_THREAD WL_THREAD;

typedef struct {
  int     temp;
}WL_THREAD_ATTR;

int WLThreadCreate(WL_THREAD **thr, const WL_THREAD_ATTR *attr, const char *thread_name, void *(*fun)(void *), void *fun_arge);

void WLThreadDestroy(WL_THREAD *thr,void **re_data);


#endif