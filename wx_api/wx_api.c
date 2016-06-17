/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  wx_api.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/14/2016 02:14:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), 544088192@qq.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */
//#include <stdio.h>
//#include <stdlib.h>
#define PYTHON_IMPLEMENT            /*  */
#ifdef PYTHON_IMPLEMENT
#include <Python.h>
#endif

#include "wx_api.h"
#include "debug.h"

#include <libgen.h>

#define __PATH_MAX            256            /*  */
#define RET_MAX            512/*  */

#ifdef PYTHON_IMPLEMENT
static const char * excute_python(int argc, const char **argv, const char *func_name)
{
    char *python_name = NULL;
    char *dir_name = NULL;
    int i = 0;
    char cmd_buf[__PATH_MAX]={0};
    char tmp_buf[__PATH_MAX]={0};
    static char ret_buf[RET_MAX]={0};
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs; 
    PyObject *pRetVal;
    
    if (argc < 2)
    {
        return NULL;
    }
    strcpy(tmp_buf, argv[0]);
    python_name = basename((char *)&tmp_buf[0]);
    dir_name    = dirname((char *)&tmp_buf[0]);

    Py_Initialize(); 
    if ( !Py_IsInitialized() ) 
    { 
        return NULL; 
    } 

    PyRun_SimpleString("import sys"); 
    sprintf(cmd_buf, "sys.path.append(\'%s\')", dir_name);
    PyRun_SimpleString(cmd_buf); 

    pName = PyString_FromString(python_name); 
    pModule = PyImport_Import(pName); 
    if ( !pModule ) 
    { 
        printf("can't find pytestfuSDK.py"); 
        getchar(); 
        return NULL; 
    } 
    pDict = PyModule_GetDict(pModule); 
    if ( !pDict ) 
    { 
        return NULL; 
    } 

    pFunc = PyDict_GetItemString(pDict, func_name); 
    if ( !pFunc || !PyCallable_Check(pFunc) ) 
    { 
        printf("can't find function [add]"); 
        getchar(); 
        return NULL; 
    } 
    pArgs = PyTuple_New(argc - 1); 
    for (i = 0; i<argc-1; i++)
    {
        PyTuple_SetItem(pArgs, i, Py_BuildValue("s", argv[i+1])); 
    }
#if 0
    PyTuple_SetItem(pArgs, i, Py_BuildValue("s", "121212123")); 
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", "贡献一角钱")); 
    PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", "1")); 
    PyTuple_SetItem(pArgs, 3, Py_BuildValue("s", "3333333")); 
    PyTuple_SetItem(pArgs, 4, Py_BuildValue("s", "NATIVE")); 
#endif
    pRetVal = PyObject_CallObject(pFunc, pArgs); 
//    printf("function return value : %s\r\n", PyString_AS_STRING(pRetVal));
    if (argc > 1 && pRetVal)
    {
        memset(ret_buf, 0, sizeof (ret_buf));
        sprintf(ret_buf, "%s", PyString_AS_STRING(pRetVal));
        WX_DBG("%s\n", ret_buf);
    }

    Py_DECREF(pName); 
    Py_DECREF(pArgs); 
    Py_DECREF(pModule); 
    Py_Finalize(); 
    return (const char *)ret_buf;
   
}
#endif
#ifdef PYTHON_IMPLEMENT
wx_ret_e wx_request_order(wx_pay_account_t *account, wx_order_info_t *order, char *code_url)
{
    const char *argv [7]={0};
    const char *ret_str = NULL;
    wx_ret_e ret = WX_SUCCESS;

    if (!account || !order || !code_url)
    {
        return WX_PARAM_ERROR;
    }
    argv [0] = "./wzhifSDK";
    argv [1] = order->out_trade_no;
    argv [2] = order->name;
    argv [3] = order->total_fee;
    argv [4] = order->type == NATIVE ? "NATIVE":"UNKNOW";
    argv [5] = order->notify_url;
    ret_str = excute_python(6, argv, "test_req_order");
    if (ret_str)
    {
        if ( 0 == strncmp("-1:", ret_str, strlen("-1")))
        {
            ret = WX_UNKNOWERR;
            if ( 0 == strcmp(&ret_str[3], "签名错误"))
            {
                ret = WX_SIGNERROR;
            }
            if ( 0 == strcmp(&ret_str[3], "appid不存在") ||
                 0 == strcmp(&ret_str[3], "mch_id参数格式错误")||
                 0 == strcmp(&ret_str[3], "商户号mch_id或sub_mch_id不存在")
                 )
            {
                ret = WX_PARAM_ERROR;
            }
        }

        if (ret == WX_SUCCESS)
        {
            strcpy(code_url, ret_str);
        }
    }
    return ret;
}
int wx_gen_qrcode(const char *code_url, const char *qr_path, const char *qr_name)
{
    char cmd_buf[256]={0};

    if (!code_url || !qr_path || !qr_name)
    {
        return -1;
    }
    sprintf(cmd_buf, "qrencode %s -o %s/%s", code_url, qr_path, qr_name);
    system(cmd_buf);
    return 0;
}
wx_ret_e wx_order_query(wx_pay_account_t *account, const char *out_trade_no)
{
    const char *argv [3]={0};
    const char *ret_str = NULL;
    wx_ret_e ret = WX_SUCCESS;

    if (!account || !out_trade_no)
    {
        return WX_PARAM_ERROR;
    }
    argv[0] = "./wzhifSDK";
    argv[1] = out_trade_no;
    ret_str = excute_python(2, argv, "test_order_query");
    if (ret_str)
    {
        if ( 0 == strncmp("-1:", ret_str, strlen("-1")))
        {
            ret = WX_UNKNOWERR;
            if ( 0 == strcmp(&ret_str[3], "NOTPAY"))
            {
                ret = WX_ORDERNOTPAY;
            }
//            if ( 0 == strcmp(&ret_str[3], "appid不存在"))
//            {
//                ret = WX_PARAM_ERROR;
//            }
            if ( 0 == strcmp(&ret_str[3], "签名错误"))
            {
                ret = WX_SIGNERROR;
            }
        }
        if (0 == strncmp("PAY", ret_str, strlen("PAY")))
        {
            ret = WX_ORDERPAID;
        }
    
//        return WX_ORDERPAID;
    }
    return ret;
}
#else
wx_ret_e wx_request_order(wx_pay_account_t *accout, wx_order_info_t *order, char *code_url)
{
    return 0;
}
int wx_gen_qrcode(const char *code_url, const char *qr_path, const char *qr_name)
{
    return 0;
}
wx_ret_e wx_order_query(wx_pay_account_t *accout, const char *out_trade_no)
{
    return 0;
}
#endif
wx_ret_e wx_set_account(wx_pay_account_t *account)
{
    return 0;
}
wx_ret_e wx_get_account(wx_pay_account_t *account)
{
    return 0;
}
