//
//
// Copyright 2018 
// author: ChenFawang
// wl_log.h
// 2018 - 12 - 23
// mail: cfwang_9984@163.com
//
#ifndef __BASE_WIN_WL_LOG_H__
#define __BASE_WIN_WL_LOG_H__


#include <stdio.h>
#include <string.h>
#include <time.h>


typedef struct {
  int         s32Enlog;    // 1: open log 0: close log
  int         s32EnTime;   // 1: open time of log 0: close time of log
  int         s32EnLine;   // 1: open line of log 0: close line of log
}ONE_LOG_ATTR_S;

typedef struct {
  FILE                *pFileFp;    // pFileFp = NULL: log printf to console, pFileFp != NULL: log write to file of pFileFp
  ONE_LOG_ATTR_S      stErrorLogAttr;
  ONE_LOG_ATTR_S      stInfoLogAttr;
}LOG_ATTR_S;
extern LOG_ATTR_S log_attr_ =              // #####################don't change this value, only use LogSetAttr interface to change
{
  NULL,
  {1,1,1},
  {1,1,1}
};
#define PRINTF(fp,format,...)        do{\
                                    if((fp)!=NULL) {\
                                      fprintf((fp),format,##__VA_ARGS__);\
                                    }else{\
                                      printf(format,##__VA_ARGS__);\
                                    }\
                                  }while(0);

#define filename(x)		strrchr(x,'\\')?strrchr(x,'\\')+1:x


#define DEBUG_LINE(fp)	          do{\
                                    PRINTF((fp),"%s:%d",filename(__FILE__),__LINE__);\
                                }while(0);

#define DEBUG_TIME(fp)            // TODO





#define LogInfo(format,...)			    do{\
                                      if(log_attr_.stInfoLogAttr.s32Enlog==1) {\
                                        if(log_attr_.stInfoLogAttr.s32EnLine==1){\
                                          DEBUG_LINE(log_attr_.pFileFp);\
                                          PRINTF(log_attr_.pFileFp," ");\
                                        }\
                                        PRINTF(log_attr_.pFileFp,format,##__VA_ARGS__);\
                                      }\
                                    }while(0);


#define LogError(format,...)			do{\
                                    if(log_attr_.stErrorLogAttr.s32Enlog==1) {\
                                      if(log_attr_.stErrorLogAttr.s32EnLine==1){\
                                        DEBUG_LINE(log_attr_.pFileFp);\
                                        PRINTF(log_attr_.pFileFp," ");\
                                      }\
                                      PRINTF(log_attr_.pFileFp,format,##__VA_ARGS__);\
                                    }\
                                  }while(0);

void LogSetAttr(const LOG_ATTR_S *attr);

void LogGetAttr(LOG_ATTR_S *attr);

#endif
