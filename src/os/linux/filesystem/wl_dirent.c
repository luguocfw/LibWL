//
//
// Copyright 
// author: ChenFawang
// wl_dirent.c
// 2019 - 1 - 31
// mail: cfwang_9984@163.com
//
#include <wl_dirent.h>
#include <wl_type.h>
#include <wl_memory.h>
#include <base/wl_list.h>

#include <dirent.h>
#include <sys/types.h>

typedef struct {
  WL_DIRENT         re_dirent;
  int64_t           dir_offset;
}WL_NODE_DATA;

struct WL_DIR {
  DIR                 *dir;
  WL_LIST_HEAD_S      *read_list;
  WL_LIST_S           *cur_pos;
};

static void WLLoadAllDirent(DIR *dir, WL_LIST_HEAD_S *list_head) {
  struct dirent *sys_dirent = NULL;
  while (1) {
    WL_NODE_DATA *node = (WL_NODE_DATA *)WLMalloc(sizeof(WL_NODE_DATA));
    if (node == NULL) {
      break;
    }
    node->dir_offset = telldir(dir->dir);
    if (node->dir_offset < 0) {
      node->dir_offset = WL_ERR_UNKNOW;
    }
    sys_dirent = readdir(dir->dir);
    if (sys_dirent == NULL) {
      WLFree(node);
      break;
    }
    node->re_dirent.name_len = sys_dirent->d_reclem;
    node->re_dirent.name = sys_dirent->d_name;
    if (sys_dirent->d_type == DT_REG) {
      node->re_dirent.type = WL_DIR_FILE;
    }
    else if (sys_dirent->d_type == DT_DIR) {
      node->re_dirent.type == WL_DIR_DIR;
    }
    else {
      node->re_dirent.type = WL_DIR_UNKNOW;
    }
    node->re_dirent.size = 0;
    int ret = WLListAddNode(dir->read_list, node);
    if (ret != 0) {
      WLFree(node);
      break;
    }
  }
}

static void WLUnloadAllDirent(WL_LIST_HEAD_S *list_head) {
  WL_LIST_S *node = list_head->stList;
  while (node != NULL) {
    WLFree(node->pData);
    node->pData = NULL;
    node = node->stNextNode;
  }
}

WL_DIR *WLOpenDir(const char *path) {
  if (path == NULL) {
    return NULL;
  }
  struct WL_DIR *wl_dir = (struct WL_DIR *)WLMalloc(sizeof(struct WL_DIR));
  if (wl_dir == NULL) {
    return  NULL;
  }
  wl_dir->dir = opendir(path);
  if (wl_dir->dir == NULL) {
    WLFree(wl_dir);
    return NULL;
  }
  wl_dir->read_list = WLListCreate();
  if (wl_dir->read_list == NULL) {
    closedir(wl_dir->dir);
    WLFree(wl_dir);
    return NULL;
  }
  WLLoadAllDirent(wl_dir->dir, wl_dir->read_list);
  wl_dir->cur_pos = wl_dir->read_list->stList;
  return wl_dir;
}

void WLCloseDir(WL_DIR *dir) {
  if (dir == NULL) {
    return;
  }
  WLUnloadAllDirent(dir->read_list);
  WLListDestroy(dir->read_list);
  closedir(dir->dir);
  WLFree(dir);
}

WL_DIRENT *WLReaddir(WL_DIR *dir) {
  if (dir == NULL) {
    return NULL;
  }
  if (dir->cur_pos == NULL) {
    return NULL;
  }
  else {
    WL_DIRENT *re_value = &((WL_NODE_DATA *)dir->cur_pos->pData)->re_dirent;
    dir->cur_pos = dir->cur_pos->stNextNode;
    return re_value;
  }
}

void WLRewindDir(WL_DIR * dir) {
  if (dir == NULL) {
    return;
  }
  dir->cur_pos = dir->read_list->stList;
}

int64_t WLTelldir(WL_DIR * dir) {
  if (dir == NULL) {
    return WL_ERR_NULLPTR;
  }
  if (dir->cur_pos == NULL) {
    return 0;
  }
  return ((WL_NODE_DATA *)dir->cur_pos->pData)->dir_offset;
}

void WLSeekDir(WL_DIR * dir, uint64_t pos) {
  if (dir == NULL) {
    return;
  }
  WL_LIST_S *node = dir->read_list->stList;
  while (node != NULL) {
    WL_NODE_DATA *node_data = (WL_NODE_DATA *)node->pData;
    if (node->stNextNode == NULL) {
       dir->cur_pos = node;
       break;
    }
    else {
      WL_NODE_DATA *next_node_data = (WL_NODE_DATA *)node->stNextNode->pData;
      if (pos >= node_data->dir_offset && pos < next_node_data->dir_offset) {
        dir->cur_pos = node;
        break;
      }
    }
    node = node->stNextNode;
  }
}

char WLDirInterval() {
  return '/';
}
