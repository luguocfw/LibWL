//
//
// Copyright 
// author: ChenFawang
// wl_dirent.h
// 2019 - 1 - 31
// mail: cfwang_9984@163.com
//
#ifndef __WL_DIRENT_H__
#define __WL_DIRENT_H__
#include <stdint.h>

typedef struct WL_DIR WL_DIR;

typedef enum {
  WL_DIR_DIR=0,
  WL_DIR_FILE,
  WL_DIR_UNKNOW
}WL_DIR_TYPE;

typedef struct {
  WL_DIR_TYPE         type;
  char                *name;
  int                 name_len;
  int64_t                size;
}WL_DIRENT;

WL_DIR *WLOpenDir(const char *path);

void WLCloseDir(WL_DIR *dir);

WL_DIRENT *WLReaddir(WL_DIR *dir);

void WLRewindDir(WL_DIR *dir);

int64_t WLTelldir(WL_DIR *dir);

void WLSeekDir(WL_DIR *dir, uint64_t pos);

char WLDirInterval();

#endif