from building import *
import os
from building import *
import rtconfig

cwd  = GetCurrentDir()

src_base  = []


sample_data_template_src = []
sample_light_data_template_src = []
sample_mqtt_basic_src  = []
sample_raw_data_src  = []
sample_ota_src  = []
sample_gateway_src  = []
sample_dyn_src = []

CPPPATH = []
CPPDEFINES = []
LOCAL_CCFLAGS = ''

#include headfile
CPPPATH += [cwd + '/ports/ssl']
CPPPATH += [cwd + '/qcloud-iot-explorer-sdk-embedded-c/include']
CPPPATH += [cwd + '/qcloud-iot-explorer-sdk-embedded-c/include/exports']
CPPPATH += [cwd + '/qcloud-iot-explorer-sdk-embedded-c/sdk_src/internal_inc']

#common src file
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/protocol/mqtt/*.c')
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/services/data_template/*.c')
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/utils/*.c')
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/network/*.c')
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/network/socket/*.c')
src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/network/tls/*.c')
src_base += Glob('ports/rtthread/*.c')
SrcRemove(src_base, 'qcloud-iot-explorer-sdk-embedded-c/sdk_src/utils/qcloud_iot_ca.c')	
SrcRemove(src_base, 'ports/rtthread/HAL_UDP_rtthread.c')

CPPDEFINES += ['MQTT_COMM_ENABLED', 'AUTH_MODE_KEY']

#ota src file
if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_OTA']):
	CPPDEFINES += ['OTA_MQTT_CHANNEL']
	src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/services/ota/*.c')
	src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/protocol/http/utils_httpc.c')
	if GetDepend(['PKG_USING_OTA_HTTPS']):
		CPPDEFINES += ['OTA_USE_HTTPS']
		
#gateway src file
if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_GATEWAY']):
	src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/services/gateway/*.c')
	CPPDEFINES += ['GATEWAY_ENABLED','MULTITHREAD_ENABLED']
	
#TLS used
if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_TLS']):
	src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/utils/qcloud_iot_ca.c')
	src_base += Glob('ports/ssl/HAL_TLS_mbedtls.c')	
	if rtconfig.CROSS_TOOL == 'keil' or rtconfig.CROSS_TOOL == 'iar':
		CPPDEFINES += ['MBEDTLS_CONFIG_FILE=<tc_tls_config.h>']			
#	else: #gcc
#		import shutil
#		cp_src = cwd + '/ports/ssl/tc_tls_config.h''
#		cp_dst = cwd + '/../mbedtls-v2.7.10/ports/inc/tls_config.h'
#		shutil.copyfile(cp_src, cp_dst)		
		
else:
	CPPDEFINES += ['AUTH_WITH_NOTLS']

#dyn src file	
if GetDepend(['PKG_USING_DYN_REG']):
    sample_dyn_src += Glob('samples/dynreg_dev/dynreg_dev_sample.c')
    src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/services/dynreg/*.c')
    CPPDEFINES += ['DEV_DYN_REG_ENABLED']

group = DefineGroup('sample_dyn_reg', sample_dyn_src, depend = ['PKG_USING_DYN_REG'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)

#Err log upload used	
if GetDepend(['PKG_USING_LOG_UPLOAD']):
	src_base += Glob('qcloud-iot-explorer-sdk-embedded-c/sdk_src/services/log/*.c')
	CPPDEFINES += ['LOG_UPLOAD']

if GetDepend(['PKG_USING_MULTITHREAD_ENABLED']):	
	CPPDEFINES += ['MULTITHREAD_ENABLED']
	
#IoT Explorer C-SDK core
group = DefineGroup('tencent-iot-explorer', src_base, depend = ['PKG_USING_TENCENT_IOT_EXPLORER'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)
	
#Data Template Example
if GetDepend(['PKG_USING_DATA_TEMPLATE_PROTOCOL']):
	sample_data_template_src += Glob('samples/data_template/data_template_sample.c')
	if GetDepend(['PKG_USING_EVENT_POST']):
		CPPDEFINES += ['EVENT_POST_ENABLED']
	if GetDepend(['PKG_USING_ACTION']):
		CPPDEFINES += ['ACTION_ENABLED']		
	
group = DefineGroup('sample_data_template', sample_data_template_src, depend = ['PKG_USING_DATA_TEMPLATE_PROTOCOL'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)

#Data Template light Example
if GetDepend(['PKG_USING_SMART_LIGHT_SAMPLE']): 
	sample_light_data_template_src += Glob('samples/scenarized/light_data_template_sample.c')
	
group = DefineGroup('sample_data_template_light', sample_light_data_template_src, depend = ['PKG_USING_SMART_LIGHT_SAMPLE'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)
		

#MQTT Example and Raw-data Example
if GetDepend(['PKG_USING_SELF_DEFINE_PROTOCOL']):
	if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_MQTT']):
		sample_mqtt_basic_src += Glob('samples/mqtt/mqtt_sample.c')
	if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_RAW_DATA']):
		sample_raw_data_src	+= Glob('samples/raw_data/raw_data_sample.c')
	
group = DefineGroup('tc_sample_mqtt_basic', sample_mqtt_basic_src, depend = ['PKG_USING_TENCENT_IOT_EXPLORER_MQTT'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)	
group = DefineGroup('sample_raw_data', sample_raw_data_src, depend = ['PKG_USING_TENCENT_IOT_EXPLORER_RAW_DATA'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)	

#OTA Example 
if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_OTA']):
	sample_ota_src += Glob('samples/ota/ota_mqtt_sample.c')

group = DefineGroup('sample_ota', sample_ota_src, depend = ['PKG_USING_TENCENT_IOT_EXPLORER_OTA'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)	
 
#Gateway Example 
if GetDepend(['PKG_USING_TENCENT_IOT_EXPLORER_GATEWAY']):
	sample_gateway_src += Glob('samples/gateway/*.c')

group = DefineGroup('sample_gateway', sample_gateway_src, depend = ['PKG_USING_TENCENT_IOT_EXPLORER_GATEWAY'], CPPPATH = CPPPATH, LOCAL_CCFLAGS = LOCAL_CCFLAGS, CPPDEFINES = CPPDEFINES)	
  
Return('group')
