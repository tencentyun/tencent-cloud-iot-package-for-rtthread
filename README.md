##  Tencent IOT SDK for rt-thread Package 
## 1 介绍
Tencent IOT SDK for rt-thread Package 是基于腾讯云物联网开发平台（IoT Explorer）[设备端 C-SDK] (https://github.com/tencentyun/qcloud-iot-explorer-sdk-embedded-c.git)在RThread环境开发的软件包，配合平台对设备数据模板化的定义，实现和云端基于数据模板协议的数据交互框架，开发者基于IoT_Explorer C-SDK数据模板框架，通过脚本自动生成模板代码，快速实现设备和平台、设备和应用之间的数据交互。

### 1.1 SDK架构图
![sdk-architecture](https://main.qcloudimg.com/raw/583a783ca9189bd3beb9df0991dc0bec.jpg)

### 1.2 目录结构

| 名称            | 说明 |
| ----            | ---- |
| docs            | 文档目录 |
| qcloud-iot-explorer-sdk-embedded-c         | 腾讯物联网设备端C-SDK |
| ports           | 移植文件目录 |
| samples         | 示例目录 |
| LICENSE         | 许可证文件 |
| README.md       | 软件包使用说明 |
| SConscript      | RT-Thread 默认的构建脚本 |

### 1.3 许可证

沿用`qcloud-iot-sdk-embedded-c`许可协议MIT。

## 2 软件包使用
### 2.1 menuconfig配置
- RT-Thread env开发工具中使用 `menuconfig` 使能 `Tencent-IoT` 软件包，配置产品及设备信息，并根据产品需求选择合适的应用示例修改新增业务逻辑，也可新增例程编写新的业务逻辑。

```
     --- Tencent-IoT:  Tencent Cloud IoT Explorer Platform SDK for RT-Thread    
        (0WUKPUCOTC) Config Product Id                                          
        (dev001) Config Device Name                                             
        (N6B8M91PB4YDTRCpqvOp4w==) Config Device Secret                         
        [*]   Enable dynamic register                                           
        (chBjKw1ER84AAVWZ4s19YKBT) Config Product Key                           
        [*]   Enable err log upload                                             
        [*]   Enable multi thread function                                      
        [*]   Enable TLS/DTLS                                                   
              Select Product Type (Data template protocol)  --->                
        [*]   Enable Event                                                      
        [*]   Enable Action                                                     
        [*]   Enable Smart_light Sample                                         
        [*]   Enable OTA                                                        
                Config OTA download by https or http (Download by http)  --->   
        [*]   Enable GateWay                                                    
              Version (latest)  --->
```

- 选项说明

`Config Product Id`：配置产品ID，平台创建生成。

`Config Device Name`：配置设备名，平台创建生成。

`Config Device Secret`：配置设备密钥，平台创建生成，考虑到嵌入式设备大多没有文件系统，暂时没有支持证书设备配置。

`Enable dynamic register`： 是否使能动态注册功能及示例，若使能，需配置动态注册的产品密钥。

`Enable err log upload`： 是否使能错误日志上传云端。

`Enable TLS/DTLS`： 是否使能TLS，若使能，则会关联选中mbedTLS软件包。

` Select Product Type`：产品类型为自定义产品还是[数据模板协议](https://cloud.tencent.com/document/product/1081/34916)产品。

`Enable event`：选用数据模板的前提下是否使能事件功能。

`Enable Action`：选用数据模板的前提下是否使能行为功能。
 
`Enable Smart_light Sample`：是否使能智能灯场景示例。

`Enable OTA`：是否使能OTA示例。若使能OTA可进一步选择下载使用HTTPS还是HTTP。

`Enable GateWay`：是否使能网关示例。

`Version`：软件包版本选择, v3.1.2及以后的版本只支持物联网开发平台(IoT Explorer)，若需使用物联网通信平台(IoT Hub),请选择3.0.2版本及之前的版本。

- 相关链接
 [物联网通信平台SDK说明文档](https://github.com/tencentyun/qcloud-iot-sdk-embedded-c/blob/master/docs/物联网通信平台.md)

- 使用 `pkgs --update` 命令下载软件包

### 2.2 编译及运行
1. 使用命令 scons --target=xxx 输出对应的工程，编译 

2. 执行示例程序：

### 2.3 运行demo程序
系统启动后，在 MSH 中使用命令执行：

#### 2.3.1 数据模板智能灯 + TLS示例：
- 示例说明：该示例展示了设备和[物联网开发平台](https://cloud.tencent.com/product/iotexplorer)基于[数据模板协议](https://cloud.tencent.com/document/product/1081/34916)的通信示例，关于数据模板协议参见链接说明，使能TLS，示例在物联网开发平台下发控制灯为红色的命令，设备端收取了消息，打印颜色，并上报对应消息。

- 配置选项
```
--- Tencent-IoT:  Tencent Cloud IoT Explorer Platform SDK for RT-Thread     
--- Tencent-IoT:  Tencent Cloud IoT Explorer Platform SDK for RT-Thread               
   (0WUKPUCOTC) Config Product Id                                                     
   (dev001) Config Device Name                                                        
   (N6B8M91PB4YDTRCpqvOp4w==) Config Device Secret                                    
   [ ]   Enable dynamic register                                                      
   [ ]   Enable err log upload                                                        
   [ ]   Enable multi thread function                                                 
   [*]   Enable TLS/DTLS                                                              
         Select Product Type (Data template protocol)  --->                           
   [*]   Enable Event                                                                 
   [*]   Enable Action                                                                
   [*]   Enable Smart_light Sample                                                    
   [ ]   Enable OTA                                                                   
   [ ]   Enable GateWay                                                               
         Version (latest)  --->                                                       
```

- 运行示例

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jun 15 2020
 2006 - 2020 Copyright by rt-thread team
lwIP-2.0.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/SDIO] SD card capacity 65536 KB.
hello rt-thread
msh />tc_data_template_light_example start
INF|20|qcloud_iot_device.c|iot_device_info_set(65): SDK_Ver: 3.1.1, Product_ID: 0WUKPUCOTC, Device_Name: dev001
msh />DBG|20|HAL_TLS_mbedtls.c|HAL_TLS_Connect(228):  Connecting to /0WUKPUCOTC.iotcloud.tencentdevices.com/8883...
DBG|21|HAL_TLS_mbedtls.c|HAL_TLS_Connect(233):  Setting up the SSL/TLS structure...
DBG|21|HAL_TLS_mbedtls.c|HAL_TLS_Connect(285): Performing the SSL/TLS handshake...
INF|21|mqtt_client.c|IOT_MQTT_Construct(127): mqtt connect with id: qPU1e success
DBG|21|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(141): topicName=$thing/down/property/0WUKPUCOTC/dev001|packet_id=64736
DBG|21|data_template_client.c|_template_mqtt_event_handler(242): template subscribe success, packet-id=64736
INF|21|light_data_template_sample.c|event_handler(321): subscribe success, packet-id=64736
INF|21|data_template_client.c|IOT_Template_Construct(785): Sync device data successfully
DBG|21|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(141): topicName=$thing/down/event/0WUKPUCOTC/dev001|packet_id=64737
DBG|21|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(141): topicName=$thing/down/action/0WUKPUCOTC/dev001|packet_id=64738
INF|21|light_data_template_sample.c|data_template_light_thread(650): Cloud Device Construct Success
DBG|21|light_data_template_sample.c|_usr_init(354): add your init code here
INF|21|light_data_template_sample.c|_register_data_template_property(432): data template property=power_switch registered.
INF|21|light_data_template_sample.c|_register_data_template_property(432): data template property=color registered.
INF|21|light_data_template_sample.c|_register_data_template_property(432): data template property=brightness registered.
INF|21|light_data_template_sample.c|_register_data_template_property(432): data template property=name registered.
INF|21|light_data_template_sample.c|data_template_light_thread(676): Register data template propertys Success
INF|21|light_data_template_sample.c|_register_data_template_action(294): data template action=blink registered.
INF|21|light_data_template_sample.c|data_template_light_thread(686): Register data template actions Success
DBG|21|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report_info", "clientToken":"0WUKPUCOTC-0", "params":{"module_hardinfo":"ESP8266","module_softinfo":"V1.0","fw_ver":"3.1.1","imei":"11-22-33-44","lat":"22.546015","lon":"113.941125", "device_label":{"append_info":"your self define info"}}}
DBG|21|data_template_client.c|_template_mqtt_event_handler(242): template subscribe success, packet-id=64737
INF|21|light_data_template_sample.c|event_handler(321): subscribe success, packet-id=64737
DBG|21|data_template_client.c|_template_mqtt_event_handler(242): template subscribe success, packet-id=64738
INF|21|light_data_template_sample.c|event_handler(321): subscribe success, packet-id=64738
DBG|21|data_template_client.c|_reply_ack_cb(169): replyAck=0
DBG|21|data_template_client.c|_reply_ack_cb(172): Received Json Document={"method":"report_info_reply","clientToken":"0WUKPUCOTC-0","code":0,"status":"success"}
DBG|21|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"get_status", "clientToken":"0WUKPUCOTC-1"}
DBG|21|data_template_client.c|_get_status_reply_ack_cb(185): replyAck=0
DBG|21|data_template_client.c|_get_status_reply_ack_cb(189): Received Json Document={"method":"get_status_reply","clientToken":"0WUKPUCOTC-1","code":0,"status":"success","data":{"reported":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}}
DBG|21|light_data_template_sample.c|data_template_light_thread(709): Get data status success
DBG|22|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-2", "params":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}
INF|22|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|23|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-2","code":0,"status":"success"}
DBG|27|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-3", "params":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}
INF|27|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|28|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-3","code":0,"status":"success"}
DBG|32|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-4", "params":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}
INF|32|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|33|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-4","code":0,"status":"success"}
DBG|37|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-5", "params":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}
INF|37|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|38|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-5","code":0,"status":"success"}
DBG|43|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-6", "params":{"power_switch":0,"color":0,"brightness":0,"name":"dev001"}}
INF|43|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|44|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-6","code":0,"status":"success"}
DBG|46|data_template_client_manager.c|_on_template_downstream_topic_handler(527): control_str:{"color":1,"brightness":1,"name":"","power_switch":1}
INF|46|light_data_template_sample.c|OnControlMsgCallback(405): Property=brightness changed
INF|46|light_data_template_sample.c|OnControlMsgCallback(405): Property=color changed
INF|46|light_data_template_sample.c|OnControlMsgCallback(405): Property=power_switch changed
[  lighting  ]|[color:GREEN]|[brightness:--------------------]|[dev001]
DBG|46|data_template_client.c|IOT_Template_ControlReply(698): Report Document: {"code":0, "clientToken":"clientToken-21f40729-cd65-425c-aaa8-4e6de6aecbbf"}
DBG|46|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"control_reply", "code":0, "clientToken":"clientToken-21f40729-cd65-425c-aaa8-4e6de6aecbbf"}
DBG|46|light_data_template_sample.c|data_template_light_thread(744): Contol msg reply success
DBG|46|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-7", "params":{"power_switch":1,"color":1,"brightness":1}}
INF|46|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
DBG|46|mqtt_client_publish.c|qcloud_iot_mqtt_publish(334): publish topic seq=64739|topicName=$thing/up/event/0WUKPUCOTC/dev001|payload={"method":"event_post", "clientToken":"0WUKPUCOTC-8", "eventId":"status_report", "type":"info", "timestamp":0, "params":{"status":1,"message":"light on"}}
INF|47|light_data_template_sample.c|event_handler(335): publish success, packet-id=64739
INF|47|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-7","code":0,"status":"success"}
DBG|47|data_template_event.c|_on_event_reply_callback(105): recv:{"method":"event_reply","clientToken":"0WUKPUCOTC-8","code":0,"status":"","data":{}}
DBG|47|data_template_event.c|_on_event_reply_callback(123): eventToken:0WUKPUCOTC-8 code:0 status:(null)
DBG|47|light_data_template_sample.c|event_post_cb(185): recv event reply, clear event
DBG|47|data_template_event.c|_traverse_event_list(79): eventToken[0WUKPUCOTC-8] released
DBG|48|mqtt_client_publish.c|qcloud_iot_mqtt_publish(340): publish packetID=0|topicName=$thing/up/property/0WUKPUCOTC/dev001|payload={"method":"report", "clientToken":"0WUKPUCOTC-9", "params":{"power_switch":1,"color":1,"brightness":1,"name":"dev001"}}
INF|48|light_data_template_sample.c|data_template_light_thread(761): data template reporte success
INF|49|light_data_template_sample.c|OnReportReplyCallback(416): recv report_reply(ack=0): {"method":"report_reply","clientToken":"0WUKPUCOTC-9","code":0,"status":"success"}
```

#### 2.3.2 OTA示例：
- 示例说明：该示例展示了设备基于[物联网开发平台](https://cloud.tencent.com/product/iotexplorer)实现[设备固件升级](https://cloud.tencent.com/document/product/1081/39359)，固件升级的消息通道及状态上报走MQTT，固件下载通道支持HTTPS和HTTP。
>! 若固件下载使能HTTPS，会关联选中mbedTLS软件包，需要将 `MBEDTLS_SSL_MAX_CONTENT_LEN`配置为16K

- 配置选项
```
  --- Tencent-IoT:  Tencent Cloud IoT Explorer Platform SDK for RT-Thread         
  (0WUKPUCOTC) Config Product Id                                                  
  (dev001) Config Device Name                                                     
  (N6B8M91PB4YDTRCpqvOp4w==) Config Device Secret                                 
  [ ]   Enable dynamic register                                                   
  [ ]   Enable err log upload                                                     
  [ ]   Enable multi thread function                                              
  -*-   Enable TLS/DTLS                                                           
        Select Product Type (Data template protocol)  --->                        
  [ ]   Enable Event                                                              
  [ ]   Enable Action                                                             
  [ ]   Enable Smart_light Sample                                                 
  [*]   Enable OTA                                                                
          Config OTA download by https or http (Download by https)  --->          
  [ ]   Enable GateWay                                                            
        Version (latest)  --->                                                    
```

- 运行示例

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jun 16 2020
 2006 - 2020 Copyright by rt-thread team
lwIP-2.0.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/SDIO] SD card capacity 65536 KB.
msh />rt-thread
msh />tc_ota_example start
msh />DBG|13|HAL_TLS_mbedtls.c|HAL_TLS_Connect(228):  Connecting to /0WUKPUCOTC.iotcloud.tencentdevices.com/8883...
DBG|13|HAL_TLS_mbedtls.c|HAL_TLS_Connect(233):  Setting up the SSL/TLS structure...
DBG|13|HAL_TLS_mbedtls.c|HAL_TLS_Connect(285): Performing the SSL/TLS handshake...
INF|13|mqtt_client.c|IOT_MQTT_Construct(117): mqtt connect with id: 7849s success
INF|13|ota_mqtt_sample.c|ota_thread(314): Cloud Device Construct Success
DBG|13|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$ota/update/0WUKPUCOTC/dev001|packet_id=39516
INF|13|ota_mqtt_sample.c|event_handler(69): subscribe success, packet-id=39516
DBG|13|ota_mqtt.c|_otamqtt_event_callback(124): OTA topic subscribe success
ERR|14|ota_mqtt_sample.c|get_local_fw_version(118): open file ./local_fw_info.json failed
DBG|14|ota_mqtt_sample.c|ota_thread(331): local_ver:(null) local_md5:(null), local_size:(null)
DBG|14|mqtt_client_publish.c|qcloud_iot_mqtt_publish(339): publish topic seq=39517|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_version", "report":{"version":"1.0.0"}}
INF|14|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
INF|14|ota_mqtt_sample.c|event_handler(81): publish success, packet-id=39517
DBG|14|ota_mqtt.c|_otamqtt_upgrage_cb(110): topic=$ota/update/0WUKPUCOTC/dev001
INF|14|ota_mqtt.c|_otamqtt_upgrage_cb(111): len=86, topic_msg={"result_code":0,"result_msg":"success","type":"report_version_rsp","version":"1.0.0"}
INF|14|ota_client.c|_ota_callback(103): Report version success!
INF|17|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
INF|19|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
INF|21|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
INF|24|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
INF|26|ota_mqtt_sample.c|ota_thread(342): wait for ota upgrade command...
DBG|26|ota_mqtt.c|_otamqtt_upgrage_cb(110): topic=$ota/update/0WUKPUCOTC/dev001
INF|26|ota_mqtt.c|_otamqtt_upgrage_cb(111): len=454, topic_msg={"file_size":420139,"md5sum":"de113bec77a2931b4cb3cfc42430b346","type":"update_firmware","url":"https://ota-1255858890.cos.ap-guangzhou.myqcloud.com/100005337755_0WUKPUCOTC_2.0.0?sign=q-sign-algorithm%3Dsha1%26q-ak%3DAKIDdO8ldrUa0Uts4H5Gzx6FZ9nfedjpiCd7%26q-sign-time%3D1592277704%3B1592364104%26q-key-time%3D1592277704%3B1592364104%26q-header-list%3D%26q-url-param-list%3D%26q-signature%3Dd15ec668f982ea2461316b5af6e4e86afb601b7a%00","version":"2.0.0"}

DBG|26|ota_client.c|IOT_OTA_StartDownload(347): to download FW from offset: 0, size: 420139
DBG|26|ota_fetch.c|ofc_Init(86): head_content:Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Encoding: gzip, deflate
Range: bytes=0-420139

DBG|26|HAL_TLS_mbedtls.c|_mbedtls_client_init(148): psk/pskid is empty!|psk=(null)|psd_id=
DBG|26|HAL_TLS_mbedtls.c|HAL_TLS_Connect(228):  Connecting to /ota-1255858890.cos.ap-guangzhou.myqcloud.com/443...
DBG|26|HAL_TLS_mbedtls.c|HAL_TLS_Connect(233):  Setting up the SSL/TLS structure...
DBG|26|HAL_TLS_mbedtls.c|HAL_TLS_Connect(285): Performing the SSL/TLS handshake...
DBG|27|utils_httpc.c|qcloud_http_client_connect(744): http client connect success
DBG|27|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_progress", "report": {"progress": {"state":"downloading", "percent":"0", "result_code":"0", "result_msg":""}, "version": "2.0.0"}}
DBG|27|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|27|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|27|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|28|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|28|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
                      .
                      .
DBG|44|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_progress", "report": {"progress": {"state":"downloading", "percent":"98", "result_code":"0", "result_msg":""}, "version": "2.0.0"}}
DBG|44|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|44|ota_mqtt_sample.c|ota_thread(419): 4999 bytes receved
DBG|44|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_progress", "report": {"progress": {"state":"downloading", "percent":"100", "result_code":"0", "result_msg":""}, "version": "2.0.0"}}
DBG|44|ota_mqtt_sample.c|ota_thread(419): 223 bytes receved
DBG|44|ota_client.c|IOT_OTA_Ioctl(631): origin=de113bec77a2931b4cb3cfc42430b346, now=de113bec77a2931b4cb3cfc42430b346
INF|44|ota_mqtt_sample.c|ota_thread(459): The firmware is valid
DBG|46|mqtt_client_publish.c|qcloud_iot_mqtt_publish(339): publish topic seq=39518|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_progress", "report":{"progress":{"state":"burning", "result_code":"0", "result_msg":""}, "version":"2.0.0"}}
INF|47|ota_mqtt_sample.c|event_handler(81): publish success, packet-id=39518
DBG|47|mqtt_client_publish.c|qcloud_iot_mqtt_publish(339): publish topic seq=39519|topicName=$ota/report/0WUKPUCOTC/dev001|payload={"type": "report_progress", "report":{"progress":{"state":"done", "result_code":"0", "result_msg":""}, "version":"2.0.0"}}
INF|48|ota_mqtt_sample.c|event_handler(81): publish success, packet-id=39519
INF|49|ota_mqtt.c|_otamqtt_event_callback(138): OTA topic has been unsubscribed
INF|49|mqtt_client_connect.c|qcloud_iot_mqtt_disconnect(474): mqtt disconnect!
INF|49|mqtt_client.c|IOT_MQTT_Destroy(181): mqtt release!
```

#### 2.3.2 网关示例：
- 示例说明：该示例展示了设备基于[物联网开发平台](https://cloud.tencent.com/product/iotexplorer)通过网关代理子设备上下线及消息收发，网关示例在控制台的相关操作参阅[网关设备快速入门](https://github.com/tencentyun/qcloud-iot-explorer-sdk-embedded-c/blob/master/docs/%E7%BD%91%E5%85%B3%E8%AE%BE%E5%A4%87%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8.md)。
>! 网关示例默认提供了一组测试用的网关和子设备信息，但有可能多个开发者在同时使用，这样会导致互踢。建议最好替换为自己的网关和子设备信息。

- 配置选项
```
  --- Tencent-IoT:  Tencent Cloud IoT Explorer Platform SDK for RT-Thread         
  (0WUKPUCOTC) Config Product Id                                                  
  (dev001) Config Device Name                                                     
  (N6B8M91PB4YDTRCpqvOp4w==) Config Device Secret                                 
  [ ]   Enable dynamic register                                                   
  [ ]   Enable err log upload                                                     
  [ ]   Enable multi thread function                                              
  -*-   Enable TLS/DTLS                                                           
        Select Product Type (Data template protocol)  --->                        
  [ ]   Enable Event                                                              
  [ ]   Enable Action                                                             
  [ ]   Enable Smart_light Sample                                                 
  [ ]   Enable OTA                                                                
          Config OTA download by https or http (Download by https)  --->          
  [*]   Enable GateWay                                                            
        Version (latest)  --->                                                    
```

- 运行示例
```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jun 16 2020
 2006 - 2020 Copyright by rt-thread team
lwIP-2.0.2 initialized!
[I/sal.skt] Socket Abstraction Layer initialize success.
[I/SDIO] SD card capacity 65536 KB.
hello rt-thread
msh />tc_gateway_example start
msh />DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(173): sub device num:6
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 0th subDevPid:BK7EEF4UIB subDevName:dev01
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 1th subDevPid:BK7EEF4UIB subDevName:dev02
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 2th subDevPid:BK7EEF4UIB subDevName:dev03
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 3th subDevPid:7P3KIFQ1JD subDevName:test01
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 4th subDevPid:7P3KIFQ1JD subDevName:test02
DBG|7|HAL_Device_rtthread.c|HAL_GetGwDevInfo(175): 5th subDevPid:7P3KIFQ1JD subDevName:test03
DBG|7|HAL_TLS_mbedtls.c|HAL_TLS_Connect(228):  Connecting to /0WUKPUCOTC.iotcloud.tencentdevices.com/8883...
DBG|7|HAL_TLS_mbedtls.c|HAL_TLS_Connect(233):  Setting up the SSL/TLS structure...
DBG|7|HAL_TLS_mbedtls.c|HAL_TLS_Connect(285): Performing the SSL/TLS handshake...
INF|7|mqtt_client.c|IOT_MQTT_Construct(117): mqtt connect with id: u7YuF success
DBG|7|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$gateway/operation/result/0WUKPUCOTC/dev001|packet_id=55998
DBG|7|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=55998
DBG|7|gateway_api.c|gateway_yield_thread(38): gateway yield thread start ...
DBG|8|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|8|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev01"}]}}
INF|8|gateway_common.c|_gateway_message_handler(159): client_id(BK7EEF4UIB/dev01), online result 0
DBG|8|gateway_sample.c|gateway_thread(238): subDev Pid:BK7EEF4UIB devName:dev01 online success.
DBG|8|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|8|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev02"}]}}
INF|8|gateway_common.c|_gateway_message_handler(159): client_id(BK7EEF4UIB/dev02), online result 0
DBG|8|gateway_sample.c|gateway_thread(238): subDev Pid:BK7EEF4UIB devName:dev02 online success.
DBG|8|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|8|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev03"}]}}
INF|8|gateway_common.c|_gateway_message_handler(159): client_id(BK7EEF4UIB/dev03), online result 0
DBG|9|gateway_sample.c|gateway_thread(238): subDev Pid:BK7EEF4UIB devName:dev03 online success.
DBG|9|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|9|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test01"}]}}
INF|9|gateway_common.c|_gateway_message_handler(159): client_id(7P3KIFQ1JD/test01), online result 0
DBG|9|gateway_sample.c|gateway_thread(238): subDev Pid:7P3KIFQ1JD devName:test01 online success.
DBG|9|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|9|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test02"}]}}
INF|9|gateway_common.c|_gateway_message_handler(159): client_id(7P3KIFQ1JD/test02), online result 0
DBG|9|gateway_sample.c|gateway_thread(238): subDev Pid:7P3KIFQ1JD devName:test02 online success.
DBG|9|gateway_api.c|IOT_Gateway_Subdev_Online(219): there is no session, create a new session
DBG|9|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"online","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test03"}]}}
INF|9|gateway_common.c|_gateway_message_handler(159): client_id(7P3KIFQ1JD/test03), online result 0
DBG|9|gateway_sample.c|gateway_thread(238): subDev Pid:7P3KIFQ1JD devName:test03 online success.
ERR|9|gateway_sample.c|gateway_thread(265): create sub_dev light thread success
DBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thing/down/property/BK7EEF4UIB/dev02|packet_id=55999
DBG|9|sub_dev001.c|sub_dev1_thread(556): sub_dev1_thread ...
INF|9|qcloud_iot_devDBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thing/down/property/BK7EEF4UIB/dev03|packet_id=56000
DBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thing/down/property/7P3KIFQ1JD/test01|packet_id=56001
DBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thiice.c|iot_device_info_set(55): SDK_Ver: 3.1.3, Product_ID: BK7EEF4UIB, Device_Name: dev01
ng/down/property/7P3KIFQ1JD/test02|packet_id=56002
DBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thing/down/property/BK7EEF4UIB/dev01|packet_id=56003
INF|9|sub_dev001.c|DBG|9|mqtt_client_subscribe.c|qcloud_iot_mqtt_subscribe(147): topicName=$thing/down/property/7P3KIFQ1JD/test03|packet_id=56004
suDBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=55999
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=55999
b_dev1_thread(566): Cloud Device Construct Success
DBG|9|sub_dev001.c|_usr_init(335): add your init code here
INF|9|sub_dev001.c|_register_data_template_property(376): data template property=power_switch registered.
INF|9|sub_dev001.c|_register_data_template_property(376): data template property=color registered.
INF|9|sub_dev001.c|_register_data_template_property(376): data template property=brightness registered.
INF|9|sub_dev001.c|_register_data_template_property(376): data template property=name registered.
INF|9|sub_dev001.c|sub_dev1_thread(588): Register data template propertys Success
DBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=56001
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=56001
DBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=56003
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=56003
DBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=56000
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=56000
DBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=56002
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=56002
DBG|9|gateway_api.c|_gateway_event_handler(116): gateway sub|unsub(3) success, packet-id=56004
INF|9|gateway_sample.c|_event_handler(81): subscribe success, packet-id=56004
DBG|10|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev01|payload={"method":"report_info", "clientToken":"BK7EEF4UIB-0", "params":{"module_hardinfo":"ESP8266","module_softinfo":"V1.0","fw_ver":"3.1.3","imei":"11-22-33-44","lat":"22.546015","lon":"113.941125", "device_label":{"append_info":"your self define info"}}}
DBG|10|data_template_client.c|_reply_ack_cb(194): replyAck=0
DBG|10|data_template_client.c|_reply_ack_cb(197): Received Json Document={"method":"report_info_reply","clientToken":"BK7EEF4UIB-0","code":0,"status":"success"}
DBG|10|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev01|payload={"method":"get_status", "clientToken":"BK7EEF4UIB-1"}
DBG|10|data_template_client.c|_get_status_reply_ack_cb(211): replyAck=0
DBG|10|data_template_client.c|_get_status_reply_ack_cb(215): Received Json Document={"method":"get_status_reply","clientToken":"BK7EEF4UIB-1","code":0,"status":"success","data":{"reported":{"brightness":0,"name":"","power_switch":0,"color":0}}}
DBG|11|sub_dev001.c|sub_dev1_thread(626): Get data status success
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev01|payload={"method":"report", "clientToken":"BK7EEF4UIB-2", "params":{"power_switch":0,"color":0,"brightness":0,"name":""}}
INF|11|sub_dev001.c|sub_dev1_thread(665): data template reporte success
INF|11|sub_dev001.c|OnReportReplyCallback(361): recv report_reply(ack=0): {"method":"report_reply","clientToken":"BK7EEF4UIB-2","code":0,"status":"success"}
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev02|payload={"method":"report","clientToken":"123","params":{}}
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev03|payload={"method":"report","clientToken":"123","params":{}}
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/7P3KIFQ1JD/test01|payload={"method":"report","clientToken":"123","params":{}}
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/7P3KIFQ1JD/test02|payload={"method":"report","clientToken":"123","params":{}}
DBG|11|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/7P3KIFQ1JD/test03|payload={"method":"report","clientToken":"123","params":{}}
INF|11|gateway_sample.c|_message_handler(131): Receive Message With topicName:$thing/down/property/BK7EEF4UIB/dev02, payload:{"method":"report_reply","clientToken":"123","code":0,"status":"success"}
INF|11|gateway_sample.c|_message_handler(131): Receive Message With topicName:$thing/down/property/7P3KIFQ1JD/test01, payload:{"method":"report_reply","clientToken":"123","code":0,"status":"success"}
INF|11|gateway_sample.c|_message_handler(131): Receive Message With topicName:$thing/down/property/7P3KIFQ1JD/test02, payload:{"method":"report_reply","clientToken":"123","code":0,"status":"success"}
INF|11|gateway_sample.c|_message_handler(131): Receive Message With topicName:$thing/down/property/7P3KIFQ1JD/test03, payload:{"method":"report_reply","clientToken":"123","code":0,"status":"success"}
INF|11|gateway_sample.c|_message_handler(131): Receive Message With topicName:$thing/down/property/BK7EEF4UIB/dev03, payload:{"method":"report_reply","clientToken":"123","code":0,"status":"success"}
DBG|17|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$thing/up/property/BK7EEF4UIB/dev01|payload={"method":"report", "clientToken":"BK7EEF4UIB-3", "params":{"power_switch":0,"color":0,"brightness":0,"name":""}}
INF|17|sub_dev001.c|sub_dev1_thread(665): data template reporte success
INF|17|sub_dev001.c|OnReportReplyCallback(361): recv report_reply(ack=0): {"method":"report_reply","clientToken":"BK7EEF4UIB-3","code":0,"status":"success"}
msh />tc_gateway_example stop 
msh />DBG|22|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev01"}]}}
INF|22|gateway_common.c|_gateway_message_handler(164): client_id(BK7EEF4UIB/dev01), offline result 0
DBG|22|gateway_sample.c|gateway_thread(342): subDev Pid:BK7EEF4UIB devName:dev01 offline success.
DBG|22|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev02"}]}}
INF|22|gateway_common.c|_gateway_message_handler(164): client_id(BK7EEF4UIB/dev02), offline result 0
DBG|22|gateway_sample.c|gateway_thread(342): subDev Pid:BK7EEF4UIB devName:dev02 offline success.
DBG|22|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"BK7EEF4UIB","device_name":"dev03"}]}}
INF|22|gateway_common.c|_gateway_message_handler(164): client_id(BK7EEF4UIB/dev03), offline result 0
DBG|22|gateway_sample.c|gateway_thread(342): subDev Pid:BK7EEF4UIB devName:dev03 offline success.
DBG|22|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test01"}]}}
INF|22|gateway_common.c|_gateway_message_handler(164): client_id(7P3KIFQ1JD/test01), offline result 0
DBG|23|gateway_sample.c|gateway_thread(342): subDev Pid:7P3KIFQ1JD devName:test01 offline success.
DBG|23|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test02"}]}}
INF|23|gateway_common.c|_gateway_message_handler(164): client_id(7P3KIFQ1JD/test02), offline result 0
DBG|23|gateway_sample.c|gateway_thread(342): subDev Pid:7P3KIFQ1JD devName:test02 offline success.
DBG|23|mqtt_client_publish.c|qcloud_iot_mqtt_publish(345): publish packetID=0|topicName=$gateway/operation/0WUKPUCOTC/dev001|payload={"type":"offline","payload":{"devices":[{"product_id":"7P3KIFQ1JD","device_name":"test03"}]}}
INF|23|gateway_common.c|_gateway_message_handler(164): client_id(7P3KIFQ1JD/test03), offline result 0
DBG|23|gateway_sample.c|gateway_thread(342): subDev Pid:7P3KIFQ1JD devName:test03 offline success.
INF|24|mqtt_client_connect.c|qcloud_iot_mqtt_disconnect(474): mqtt disconnect!
INF|24|mqtt_client.c|IOT_MQTT_Destroy(181): mqtt release!
```


### 2.4 控制台相关操作
#### 2.4.1 在线调试
- [物联网开发平台](https://cloud.tencent.com/product/iotexplorer)可以通过控制台直接调试，如下截图
![control](https://main.qcloudimg.com/raw/6027fc232f761b4726a13eb964721b09.jpg)

#### 2.4.2 设备日志查询
![log](https://main.qcloudimg.com/raw/5d298db54110e0c389d10e93b1efcf2b.jpg)

#### 2.4.3 设备事件查询
![event](https://main.qcloudimg.com/raw/66cfd99526d55e91778fe58e11f7d159.jpg)

### 2.5 其他示例说明
 关于 SDK 的更多使用方式及接口了解, 参见 `qcloud_iot_api_export.h`，其他示例不再一一列举。

### 2.6 可变参数配置
开发者可以根据具体场景需求，配置相应的参数，满足实际业务的运行。可变接入参数包括：
1. MQTT 心跳消息发送周期, 单位: ms 
2. MQTT 阻塞调用(包括连接, 订阅, 发布等)的超时时间, 单位:ms。 建议 5000 ms
3. TLS 连接握手超时时间, 单位: ms
4. MQTT 协议发送消息和接受消息的 buffer 大小默认是 512 字节，最大支持 256 KB
5. CoAP 协议发送消息和接受消息的 buffer 大小默认是 512 字节，最大支持 64 KB
6. 重连最大等待时间

修改 qcloud_iot_export.h 文件如下宏定义可以改变对应接入参数的配置。

```
/* MQTT心跳消息发送周期, 单位:ms */
#define QCLOUD_IOT_MQTT_KEEP_ALIVE_INTERNAL                         (240 * 1000)

/* MQTT 阻塞调用(包括连接, 订阅, 发布等)的超时时间, 单位:ms 建议5000ms */
#define QCLOUD_IOT_MQTT_COMMAND_TIMEOUT                             (5000)

/* TLS连接握手超时时间, 单位:ms */
#define QCLOUD_IOT_TLS_HANDSHAKE_TIMEOUT                            (5000)

/* MQTT消息发送buffer大小, 支持最大256*1024 */
#define QCLOUD_IOT_MQTT_TX_BUF_LEN                                  (512)

/* MQTT消息接收buffer大小, 支持最大256*1024 */
#define QCLOUD_IOT_MQTT_RX_BUF_LEN                                  (512)

/* COAP 发送消息buffer大小，最大支持64*1024字节 */
#define COAP_SENDMSG_MAX_BUFLEN                                     (512)

/* COAP 接收消息buffer大小，最大支持64*1024字节 */
#define COAP_RECVMSG_MAX_BUFLEN                                     (512)

/* 重连最大等待时间 */
#define MAX_RECONNECT_WAIT_INTERVAL                                 (60000)

```