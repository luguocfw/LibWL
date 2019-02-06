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
#include <direct.h>
#include <stdio.h>
#include <io.h>
#include <string.h>

typedef struct {
  WL_DIRENT             re_dirent;
  long                  dir_offset;
  struct _finddata_t    fa;
}WL_NODE_DATA;

struct WL_DIR {
  long            dir_handle;
  WL_LIST_HEAD_S      *read_list;
  WL_LIST_S           *cur_pos;
  long                total_offset;
};

static void WLDirentCover(struct _finddata_t *fa_in, WL_DIRENT *dirent_out) {
  dirent_out->name = fa_in->name;
  dirent_out->name_len = strlen(dirent_out->name);
  dirent_out->size = fa_in->size;
  if (((fa_in->attrib & _A_SUBDIR) == 0x00)) {
    dirent_out->type = WL_DIR_FILE;
  }
  else {
    dirent_out->type = WL_DIR_DIR;
  }
}

static int WLLoadAllDir(const char *path, WL_DIR *dir) {
  dir->total_offset = 0;
  int str_len = strlen(path);
  char *path_temp = WLMalloc(str_len + 3);
  if (path_temp == NULL) {
    return WL_ERR_NOMEM;
  }
  strcpy(path_temp, path);
  if (path_temp[str_len - 1] != WLDirInterval()) {
    path_temp[str_len] = WLDirInterval();
    str_len++;
  }
  path_temp[str_len] = '*';
  path_temp[str_len + 1] = '\0';
  long total_offset = 0;
  WL_NODE_DATA *first_node = (WL_NODE_DATA *)WLMalloc(sizeof(WL_NODE_DATA));
  if (first_node == NULL) {
    WLFree(path_temp);
    return WL_ERR_NOMEM;
  }
  long win_handle = _findfirst(path_temp, &first_node->fa);
  if (win_handle == -1) {
    WLFree(first_node);
    WLFree(path_temp);
    return WL_ERR_UNKNOW;
  }
  WLDirentCover(&first_node->fa, &first_node->re_dirent);
  first_node->dir_offset = total_offset;
  total_offset += first_node->re_dirent.size;
  int ret = WLListAddNode(dir->read_list, first_node);
  if (ret != WL_SUCCESS) {
    _findclose(win_handle);
    WLFree(first_node);
    WLFree(path_temp);
    return WL_ERR_UNKNOW;
  }
  WLFree(path_temp);
  while (1) {
    WL_NODE_DATA *node = (WL_NODE_DATA *)WLMalloc(sizeof(WL_NODE_DATA));
    if (node == NULL) {
      break;
    }
    if (_findnext(win_handle, &node->fa) != 0) {
      WLFree(node);
      break;
    }
    WLDirentCover(&node->fa, &node->re_dirent);
    node->dir_offset = total_offset;
    total_offset += node->re_dirent.size;
    ret = WLListAddNode(dir->read_list, node);
    if (ret != 0) {
      WLFree(node);
      break;
    }
  }
  dir->dir_handle = win_handle;
  dir->total_offset = total_offset;
  return WL_SUCCESS;
}
static void WLUnloadAllDir(WL_LIST_HEAD_S *list_head, long handle) {
  WL_LIST_S *node = list_head->stList;
  while (node != NULL) {
    WLFree(node->pData);
    node = node->stNextNode;
  }
  _findclose(handle);
}

WL_DIR *WLOpenDir(const char *path) {
  if (path == NULL) {
    return NULL;
  }
  WL_DIR *dir = (WL_DIR *)WLMalloc(sizeof(WL_DIR));
  if (dir == NULL) {
    return NULL;
  }
  dir->read_list = WLListCreate();
  if (dir->read_list == NULL) {
    WLFree(dir);
    return NULL;
  }
  if (WLLoadAllDir(path,dir) != WL_SUCCESS) {
    WLListDestroy(dir->read_list);
    WLFree(dir);
    return NULL;
  }
  dir->cur_pos = dir->read_list->stList;
  return dir;
}

void WLCloseDir(WL_DIR *dir) {
  if (dir == NULL) {
    return;
  }
  WLUnloadAllDir(dir->read_list, dir->dir_handle);
  WLListDestroy(dir->read_list);
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

void WLRewindDir(WL_DIR *dir) {
  if (dir == NULL) {
    return;
  }
  dir->cur_pos = dir->read_list->stList;
}

long WLTelldir(WL_DIR *dir) {
  if (dir == NULL) {
    return WL_ERR_NULLPTR;
  }
  if (dir->cur_pos == NULL) {
    return dir->total_offset;
  }
  return ((WL_NODE_DATA *)dir->cur_pos->pData)->dir_offset;
}

void WLSeekDir(WL_DIR *dir, long pos) {
  if (dir == NULL) {
    return;
  }
  if (pos < 0) {
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
  return '\\';
}
