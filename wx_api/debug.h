/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  debug.h
 *
 *    Description:
 *         Others:
 *
 *        Version:  1.0
 *        Created:  04/25/2016 11:12:58 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*  #####   DEBUG MACROS   ########################################################### */
#define     INOUT_DEBUG                           1  /* 1 is open , o is close */

#define     PRT_DEBUG                             1  /* 1 is open , o is close */
#define     PRT_ERROR                             1  /* 1 is open , 0 is close */

#define     WIFI_ERROR                            1  /* 1 is open , 0 is close */
#define     WIFI_DEBUG                            1  /* 1 is open , 0 is close */

#define     RFID_DEBUG				              1	/* 1 is open , 0 is close */

#define     WX_ERROR                              1  /* 1 is open , 0 is close */
#define     WX_DEBUG                              1  /* 1 is open , 0 is close */


#define     CAME_ERROR                            1  /* 1 is open , 0 is close */
#define     CAME_DEBUG                            1  /* 1 is open , 0 is close */

#if INOUT_DEBUG
#define FUN_IN(fmt, args...)            printf("[in][\033[1mINFO\033[0m]: ===> %s():"fmt"\n", __func__, ##args)/*   */
#define FUN_OUT(fmt, args...)           printf("[out][\033[1mINFO\033[0m]: <=== %s():"fmt"\n", __func__, ##args)/*   */
#else
#define FUN_IN(fmt, args...)
#define FUN_OUT(fmt, args...)
#endif

#if PRT_DEBUG
#define PRT_DBG(fmt, args...) printf("[prt][\033[1;34mDEBUG\033[0m]: ---> %s():"fmt"\n", __func__, ##args)/*  */
#else
#define PRT_DBG(fmt, args...)
#endif

#if PRT_ERROR
#define PRT_ERR(fmt, args...)                                                             \
    do                                                                                          \
{                                                                                           \
        printf("[prt][\033[1;31mERROR\033[0m] ---> %s ():line[%d]:", __func__, __LINE__);      \
        printf(" "fmt"\n", ##args);                                                                 \
}while(0)    /*  */
#else
#define PRT_ERR(fmt, args...)
#endif


#if WIFI_DEBUG
#define WIFI_DBG(fmt, args...) printf("[wifi][\033[1;34mDEBUG\033[0m]: ---> %s():"fmt"\n", __func__, ##args)/*  */
#else
#define WIFI_DBG(fmt, args...)
#endif

#if WIFI_ERROR
#define WIFI_ERR(fmt, args...)                                                             \
    do                                                                                          \
{                                                                                           \
        printf("[wifi][\033[1;31mERROR\033[0m] ---> %s ():line[%d]:", __func__, __LINE__);      \
        printf(" "fmt"\n", ##args);                                                                 \
}while(0)    /*  */
#else
#define WIFI_ERR(fmt, args...)
#endif

#if RFID_DEBUG
#define RFID_DBG(fmt, args...)            printf("[RFID][\033[1;34mDEBUG\033[0m]:---> %s():"fmt"\n", __func__, ##args)/*   */
#else
#define RFID_DBG(fmt, args...)
#endif

#if WX_DEBUG
#define WX_DBG(fmt, args...) printf("[wx][\033[1;34mDEBUG\033[0m]: ---> %s():"fmt"\n", __func__, ##args)/*  */
#else
#define WX_DBG(fmt, args...)
#endif

#if WX_ERROR
#define WX_ERR(fmt, args...)                                                             \
    do                                                                                          \
{                                                                                           \
        printf("[wx][\033[1;31mERROR\033[0m] ---> %s ():line[%d]:", __func__, __LINE__);      \
        printf(" "fmt"\n", ##args);                                                                 \
}while(0)    /*  */
#else
#define WX_ERR(fmt, args...)
#endif


#if CAME_DEBUG
#define CAME_DBG(fmt, args...) printf("[camera][\033[1;34mDEBUG\033[0m]: ---> %s():"fmt"\n", __func__, ##args)/*  */
#else
#define CAME_DBG(fmt, args...)
#endif

#if CAME_DEBUG
#define CAME_ERR(fmt, args...)                                                             \
    do                                                                                          \
{                                                                                           \
        printf("[camera][\033[1;31mERROR\033[0m] ---> %s ():line[%d]:", __func__, __LINE__);      \
        printf(" "fmt"\n", ##args);                                                                 \
}while(0)    /*  */
#else
#define CAME_ERR(fmt, args...)
#endif


#endif
