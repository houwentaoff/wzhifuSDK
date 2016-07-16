/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Jz.
 *       Filename:  wx_api.h
 *
 *    Description:  
 *         Others:
 *
 *        Version:  1.0
 *        Created:  06/14/2016 02:18:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Joy. Hou (hwt), 544088192@qq.com
 *   Organization:  Jz
 *
 * =====================================================================================
 */
#ifndef __WX_API_H__
#define __WX_API_H__

#define RESERVED_MAX            100            /*  */

#define  WX_RequestOrder(x,y,z)      wx_request_order(x,y,z)            /*  */
#define  WX_OrderQuery(x,y)          wx_order_query(x,y)            /*  */
#define  WX_GenQrCode(x,y,z)         wx_gen_qrcode(x,y,z)         /*  */
#define  WX_SetAccount(x)            wx_set_account(x)            /*  */
#define  WX_GetAccount(x)            wx_get_account(x)            /*  */
#define  WX_GetTimeStamp()            wx_get_time_stamp()            /*  */

typedef struct wx_pay_account
{
   char *app_id;
   char *app_secret;
   char *mch_id;
   char *key;
   int curl_timeout;
   /* 保留字段 */
   char *sslcert_path;
   char *sslkey_path;
   char reserved[RESERVED_MAX];

}wx_pay_account_t;

typedef enum trade_type
{
    NATIVE,
}trade_type_e;

typedef enum 
{
    WX_SUCCESS = 0,/* 成功 */
    WX_ORDERPAID,/* 订单已支付 */
    WX_ORDERNOTPAY,/* 订单未支付 */
    WX_ORDERCLOSED,/* 订单已关闭 */
    WX_ORDERNOTEXIST,/* 订单不存在 */
    WX_NOTENOUGH,/* 余额不足 */
    WX_PARAM_ERROR,/* 参数错误 */
    WX_NOAUTH,/* 权限不足 */
    WX_BANKERROR,/* 银行系统异常 */
    WX_SIGNERROR,/* 签名错误 */
    WX_UNKNOWERR,/* 未识别的错误 */
    
}wx_ret_e;

typedef struct wx_order_info
{
    char *out_trade_no;/* num */
    char *name;/* body */
    trade_type_e type;/* trade  */
    char *total_fee;/* 金额总数 */
    char *notify_url;
}wx_order_info_t;

/**
 * @brief 返回当前微信产生订单的时间戳 如 201606171139
 *
 * @return 
 */
const char *wx_get_time_stamp();
/**
 * @brief 向微信后端发送订单请求
 *
 * @param accout   微信支付账户信息
 * @param order    微信支付订单信息
 * @param code_url 返回二维码短连接
 *
 * @return 成功返回WX_SUCCESS 失败返回对应的错误码;
 */
wx_ret_e wx_request_order(wx_pay_account_t *accout, wx_order_info_t *order, char *code_url);
/**
 * @brief  二维码由打印机产生，该接口保留
 *         
 * @param code_url  qr二维码短链接
 * @param qr_path   qr二维码图片产生路径
 * @param qr_name   qr二维码图片名字
 *
 * @return 产生成功返回0  失败返回-1
 */
int wx_gen_qrcode(const char *code_url, const char *qr_path, const char *qr_name);
/**
 * @brief 
 *
 * @param accout        微信支付账户信息
 * @param out_trade_no  支付订单号
 *
 * @return 支付完成返回WX_ORDERPAID 否则返回错误码
 */
wx_ret_e wx_order_query(wx_pay_account_t *accout, const char *out_trade_no);

/**
 * @brief 设置用户账号信息
 *
 * @param account 参考wx_pay_account_t结构
 *
 * @return 成功返回WX_SUCCESS 错误返回错误码
 */
#ifdef WX_PAY
wx_ret_e wx_set_account(wx_pay_account_t *account);
#else
static inline wx_ret_e wx_set_account(wx_pay_account_t *account)
{
    return WX_SUCCESS;
}
#endif

/**
 * @brief 获得用户账号信息
 *
 * @param account 参考wx_pay_account_t结构
 *
 * @return 成功返回WX_SUCCESS 错误返回错误码
 */
#ifdef WX_PAY
wx_ret_e wx_get_account(wx_pay_account_t *account);
#else
static inline wx_ret_e wx_get_account(wx_pay_account_t *account)
 {
     return WX_SUCCESS;
 }
#endif

#endif
