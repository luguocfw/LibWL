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
  long                size;
}WL_DIRENT;

WL_DIR *WLOpenDir(const char *path);

void WLCloseDir(WL_DIR *dir);

WL_DIRENT *WLReaddir(WL_DIR *dir);

void WLRewindDir(WL_DIR *dir);

long WLTelldir(WL_DIR *dir);

void WLSeekDir(WL_DIR *dir, long pos);

char WLDirInterval();

#endif