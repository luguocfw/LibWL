//
//
// Copyright 2018, sohu
// author: ChenFawang
// wl_list.h
// 2019 - 1 - 31
// mail: fawangchen@sohu-inc.com
//
#ifndef __BASE_WL_LIST_H__
#define __BASE_WL_LIST_H__

typedef struct _WL_LIST_S {
  void				*pData;
  struct _WL_LIST_S	*stNextNode;
}WL_LIST_S;

typedef struct {
  WL_LIST_S	*stList;
}WL_LIST_HEAD_S;

/*Returns the head node pointer of the linked list*/
WL_LIST_HEAD_S * WLListCreate();

/*
*The data address pointed to by "data" is added 
*to the "head" list
*/
int WLListAddNode(WL_LIST_HEAD_S *head, const void *data);

/*
*The data pointed to by "data" deletes the node in 
*the list pointed to by "head"
*
*Note: This interface does not release space for the
*"data" address
*/
int WLListDelNode(WL_LIST_HEAD_S *head,const void *data);

/*
*Destroy all nodes of the data pointed to by "head"
*Note: This interface will not destroy the node data 
*point to the space, you need to first self-destruction
*/
void WLListDestroy(WL_LIST_HEAD_S *head);


int WLListGetLength(WL_LIST_HEAD_S *head);


#endif
