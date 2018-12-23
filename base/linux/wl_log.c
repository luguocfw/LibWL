//
//
// Copyright 2018, 
// author: ChenFawang
// wl_log.c
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#include "base/linux/wl_log.h"
#include <stdio.h>


pthread_mutex_t log_mux_ = PTHREAD_MUTEX_INITIALIZER;
LOG_ATTR_S log_attr_;


void LogSetAttr(const LOG_ATTR_S *attr) {
  pthread_mutex_lock(&log_mux_);
  memcpy(&log_attr_, attr, sizeof(LOG_ATTR_S));
  pthread_mutex_unlock(&log_mux_);
}

void LogGetAttr(LOG_ATTR_S *attr) {
  pthread_mutex_lock(&log_mux_);
  memcpy(attr, &log_attr_, sizeof(LOG_ATTR_S));
  pthread_mutex_unlock(&log_mux_);
}










