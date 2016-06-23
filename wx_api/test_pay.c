/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  test_pay.c
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/16/2016 02:19:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), houwentaoff@gmail.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "wx_api.h"
#include "debug.h"

#define TIMEZONE_OFFSET(foo) foo->tm_gmtoff
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    char code_url[100];
    wx_order_info_t order;
    wx_pay_account_t account;
    int ret = 0;
    struct tm *t;
    time_t current_time;
    int time_offset;
    char time_buf[100]={0};

    time(&current_time);

    t = localtime(&current_time);
    time_offset = TIMEZONE_OFFSET(t);
    sprintf(time_buf, "%d%d%d%d%d%d",
            1900+t->tm_year,
            1+t->tm_mon,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec);


    /*-----------------------------------------------------------------------------
     *  $input->SetOut_trade_no(WxPayConfig::MCHID.date("YmdHis"));
     *
     *  Y - 年，四位数字; 如: "1999" 
     *  m - 月份，二位数字，若不足二位则在前面补零; 如: "01" 至 "12" 
     *  d - 几日，二位数字，若不足二位则前面补零; 如: "01" 至 "31" 
     *  H - 24 小时制的小时; 如: "00" 至 "23" 
     *  i - 分钟; 如: "00" 至 "59" 
     *  s - 秒; 如: "00" 至 "59" 
     *  eg:  mchid+201606171139
     *-----------------------------------------------------------------------------*/
    order.out_trade_no = time_buf;//"12121212";
    order.name = "qincao deng";//"芹菜等合计";
    order.type = NATIVE;
    order.total_fee = "2";
    order.notify_url = "aaa";
    /*-----------------------------------------------------------------------------
     *  1. get url_code
     *  2. 等待直到支付完成
     *-----------------------------------------------------------------------------*/
#if 1   
    if ( WX_SUCCESS != (ret = wx_request_order(&account, &order, code_url)))
    {
        WX_ERR("req order fail error[%d]\n", ret);   
        goto req_err;
    }
    WX_DBG("req order success code_url is [%s]\n", code_url);
    wx_gen_qrcode(code_url, "./", "pay.png");
#endif
    while (1)
    {
        sleep(1);
        if ( WX_ORDERPAID != (ret = wx_order_query(&account, order.out_trade_no)))
        {
            WX_DBG("query pay status fail error[%d]\n", ret);
            continue;
        }
        else
        {
            break;
        }
    }
    printf("pay over success\n");
    return EXIT_SUCCESS;
req_err:
    return -1;
pay_err:
    return -2;
}
