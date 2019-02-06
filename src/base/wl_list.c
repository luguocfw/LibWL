//
//
// Copyright 2018, sohu
// author: ChenFawang
// wl_list.c
// 2019 - 1 - 31
// mail: fawangchen@sohu-inc.com
//
#include "base/wl_list.h"
#include <wl_memory.h>
#include <wl_type.h>
#include <stdlib.h>

WL_LIST_HEAD_S * WLListCreate() {
  WL_LIST_HEAD_S *head_node = WLMalloc(sizeof(WL_LIST_HEAD_S));
  if (head_node == NULL) {
    return NULL;
  }
  head_node->stList = NULL;
  return head_node;
}

int WLListAddNode(WL_LIST_HEAD_S * head, const void * data) {
  if (head == NULL) {
    return WL_ERR_NULLPTR;
  }
  WL_LIST_S *temp;
  WL_LIST_S *add_node = WLMalloc(sizeof(WL_LIST_S));
  if (add_node == NULL) {
    return WL_ERR_NOMEM;
  }
  add_node->pData = (void *)data;
  add_node->stNextNode = NULL;
  if (head->stList == NULL) {
    head->stList = add_node;
  }
  else {
    temp = head->stList;
    while (temp->stNextNode != NULL) {
      temp = temp->stNextNode;
    }
    temp->stNextNode = add_node;
  }
  return 0;
}

int WLListDelNode(WL_LIST_HEAD_S * head, const void * data) {
  if (head == NULL) {
    return WL_ERR_NULLPTR;
  }
  WL_LIST_S *node;
  WL_LIST_S *temp;
  if (head->stList == NULL) {
    return WL_ERR_UNKNOW;
  }
  else {
    temp = head->stList;
    if (temp->pData == data) {
      head->stList = temp->stNextNode;
      WLFree(temp);
      return 0;
    }
    node = head->stList;
    temp = node;
    while (node->pData != data&&node->stNextNode != NULL) {
      temp = node;
      node = node->stNextNode;
    }
    if (node->pData == data) {
      temp->stNextNode = node->stNextNode;
      WLFree(node);
      return 0;
    }
    return WL_ERR_UNKNOW;
  }
}

void WLListDestroy(WL_LIST_HEAD_S * head) {
  if (head == NULL) {
    return;
  }
  WL_LIST_S *temp;
  WL_LIST_S *node = head->stList;
  while (node != NULL) {
    temp = node->stNextNode;
    WLFree(node);
    node = temp;
  }
  WLFree(head);
}

int WLListGetLength(WL_LIST_HEAD_S * head) {
  int length = 0;
  if (head == NULL) {
    return length;
  }
  WL_LIST_S *node = head->stList;
  while (node != NULL) {
    length++;
    node = node->stNextNode;
  }
  return length;
}
