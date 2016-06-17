/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  test_time.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/17/2016 11:51:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <time.h>

#define TIMEZONE_OFFSET(foo) foo->tm_gmtoff
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    struct tm *t;
    time_t current_time;
    int time_offset;

    time(&current_time);
    
    t = localtime(&current_time);
    time_offset = TIMEZONE_OFFSET(t);


    printf("year:%d\n"
            "month:%d\n"
            "day:%d\n"
            "hour:%d\n"
            "min:%d\n"
            "sec:%d\n",
            1900+t->tm_year, 1+t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return EXIT_SUCCESS;
}
