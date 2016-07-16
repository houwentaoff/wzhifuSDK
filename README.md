# 微信支付api

## C语言接口
* 根据wzhifuSDK开发．
* 支持申请订单 和 查询付款结果．
* 支持生成当前支付二维码图片．

## 测试
### PC
1. `make test_pay PC=1`
2. `./test_pay`

### arm  
1. 修改`env.mk`中的变量`CROSS_COMPILE`
2. `cd wx_api;make`
3. `make test_pay`

## wzhifuSDK
* QQ交流群： [513457064](http://jq.qq.com/?_wv=1027&k=ektgbP) 

* 微信支付SDK
    官方PHP Demo移植而来，v3.37(https://res.wx.qq.com/paymchres/zh_CN/htmledition/download/bussiness-course3/wxm-payment-biz-api218f8e.zip)

