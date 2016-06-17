/*
 * =====================================================================================
 *       Copyright (c), 2013-2020.
 *       Filename:  test2.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/07/2016 04:09:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */


#include "Python.h" 
#include <stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    Py_Initialize(); 
    if ( !Py_IsInitialized() ) 
    { 
        return -1; 
    } 

    PyRun_SimpleString("import sys"); 
    PyRun_SimpleString("sys.path.append('./')"); 
    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs; 
    PyObject *pRetVal;

    pName = PyString_FromString("wzhifuSDK"); 
    pModule = PyImport_Import(pName); 
    if ( !pModule ) 
    { 
        printf("can't find pytestfuSDK.py"); 
        getchar(); 
        return -1; 
    } 
    pDict = PyModule_GetDict(pModule); 
    if ( !pDict ) 
    { 
        return -1; 
    } 

    pFunc = PyDict_GetItemString(pDict, "test_paystep1"); 
    if ( !pFunc || !PyCallable_Check(pFunc) ) 
    { 
        printf("can't find function [add]"); 
        getchar(); 
        return -1; 
    } 
    *pArgs; 
    pArgs = PyTuple_New(5); 
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "121212123")); 
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", "贡献一角钱")); 
    PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", "1")); 
    PyTuple_SetItem(pArgs, 3, Py_BuildValue("s", "3333333")); 
    PyTuple_SetItem(pArgs, 4, Py_BuildValue("s", "NATIVE")); 

    pRetVal = PyObject_CallObject(pFunc, pArgs); 
//    printf("function return value : %s\r\n", PyString_AS_STRING(pRetVal));

    Py_DECREF(pName); 
    Py_DECREF(pArgs); 
    Py_DECREF(pModule); 
    Py_Finalize(); 

    // 关闭Python 
    return EXIT_SUCCESS;
}
