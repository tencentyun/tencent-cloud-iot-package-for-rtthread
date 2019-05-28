/*
 * Tencent is pleased to support the open source community by making IoT Hub available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <stdarg.h>
#include <string.h>
#include <rtthread.h>
#include "rtconfig.h"
#include "qcloud_iot_import.h"
#include "qcloud_iot_export.h"

#define DEBUG_DEV_INFO_USED

#ifdef DEBUG_DEV_INFO_USED

/* 产品名称, 与云端同步设备状态时需要  */
static char sg_product_id[MAX_SIZE_OF_PRODUCT_ID + 1]	 = PKG_USING_TENCENT_IOTHUB_PRODUCT_ID;
/* 产品密钥, 与云端同步设备状态时需要  */
#ifdef PKG_USING_TENCENT_IOTHUB_DYNREG
static char sg_product_secret[MAX_SIZE_OF_PRODUCT_KEY + 1]  = PKG_USING_TENCENT_IOTHUB_PRODUCT_SECRET;
#else
static char sg_product_secret[MAX_SIZE_OF_PRODUCT_KEY + 1]  = "YOUR_PRODUCT_SECRET";
#endif
/* 设备名称, 与云端同步设备状态时需要 */
static char sg_device_name[MAX_SIZE_OF_DEVICE_NAME + 1]  = PKG_USING_TENCENT_IOTHUB_DEVICE_NAME;

#ifdef AUTH_MODE_CERT
/* 客户端证书文件名  非对称加密使用, TLS 证书认证方式*/
static char sg_device_cert_file_name[MAX_SIZE_OF_DEVICE_CERT_FILE_NAME + 1]      = "YOUR_DEVICE_NAME_cert.crt";
/* 客户端私钥文件名 非对称加密使用, TLS 证书认证方式*/
static char sg_device_privatekey_file_name[MAX_SIZE_OF_DEVICE_KEY_FILE_NAME + 1] = "YOUR_DEVICE_NAME_private.key";
#else
/* 设备密钥, TLS PSK认证方式*/
static char sg_device_secret[MAX_SIZE_OF_DEVICE_SERC + 1] = PKG_USING_TENCENT_IOTHUB_DEVICE_SECRET;
#endif

#endif


#define HAL_OS_LOG_MAXLEN   1024
static uint16_t g_mutex_count = 0;



void HAL_Printf(_IN_ const char *fmt, ...)
{
    va_list args;
	char log_buf[HAL_OS_LOG_MAXLEN];
    
    va_start(args, fmt);
    rt_vsnprintf(log_buf, HAL_OS_LOG_MAXLEN, fmt, args);
    va_end(args);
    printf("%s", log_buf);
}


int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int rc;

    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);

    return rc;
}


int HAL_Vsnprintf(_IN_ char *str, _IN_ const int len, _IN_ const char *format, va_list ap)
{
    return vsnprintf(str, len, format, ap);
}


void *HAL_MutexCreate(void)
{
	rt_mutex_t mutex;
	char mutexName[RT_NAME_MAX];

	memset(mutexName, 0, RT_NAME_MAX);
	HAL_Snprintf(mutexName, RT_NAME_MAX, "tmutex_%d", g_mutex_count++);	
	mutex = rt_mutex_create(mutexName, RT_IPC_FLAG_FIFO);
    if (NULL == mutex) {
		HAL_Printf("create mutex failed");

    }

    return mutex;


}

void HAL_MutexDestroy(_IN_ void *mutex)
{
	int err_num;

	err_num = rt_mutex_delete((rt_mutex_t)mutex);

    if (0 != err_num) 
	{
        HAL_Printf("destroy mutex failed");
    }
}

void HAL_MutexLock(_IN_ void *mutex)
{
	int err_num;
	
	err_num = rt_mutex_take((rt_mutex_t)mutex, RT_WAITING_FOREVER);

    if (0 != err_num)
	{
        HAL_Printf("lock mutex failed");
    }
}

void HAL_MutexUnlock(_IN_ void *mutex)
{
    int err_num;

	err_num = rt_mutex_take((rt_mutex_t)mutex, RT_WAITING_FOREVER);
	 
    if (0 != err_num)
	{
        HAL_Printf("lock mutex failed");
    }

}

void *HAL_Malloc(_IN_ uint32_t size)
{
   return rt_malloc(size);
}

void HAL_Free(_IN_ void *ptr)
{
    rt_free(ptr);
}

void HAL_SleepMs(_IN_ uint32_t ms)
{
    (void)rt_thread_delay(rt_tick_from_millisecond(ms));
}

int HAL_GetProductID(char *pProductId, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_product_id) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pProductId, '\0', maxlen);
	strncpy(pProductId, sg_product_id, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetProductID is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}

int HAL_GetProductKey(char *pProductKey, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_product_secret) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pProductKey, '\0', maxlen);
	strncpy(pProductKey, sg_product_secret, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetProductKey is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}


int HAL_GetDevName(char *pDevName, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_device_name) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pDevName, '\0', maxlen);
	strncpy(pDevName, sg_device_name, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetDevName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}


int HAL_SetProductID(const char *pProductId)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pProductId) > MAX_SIZE_OF_PRODUCT_ID){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_product_id, '\0', MAX_SIZE_OF_PRODUCT_ID);
	strncpy(sg_product_id, pProductId, MAX_SIZE_OF_PRODUCT_ID);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetProductID is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}


int HAL_SetProductKey(const char *pProductKey)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pProductKey) > MAX_SIZE_OF_PRODUCT_KEY){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_product_secret, '\0', MAX_SIZE_OF_PRODUCT_KEY);
	strncpy(sg_product_secret, pProductKey, MAX_SIZE_OF_PRODUCT_KEY);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetDevName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif

}

int HAL_SetDevName(const char *pDevName)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pDevName) > MAX_SIZE_OF_DEVICE_NAME){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_device_name, '\0', MAX_SIZE_OF_DEVICE_NAME);
	strncpy(sg_device_name, pDevName, MAX_SIZE_OF_DEVICE_NAME);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetDevName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}
#ifdef AUTH_MODE_CERT	//证书 认证方式

int HAL_GetDevCertName(char *pDevCert, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_device_cert_file_name) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pDevCert, '\0', maxlen);
	strncpy(pDevCert, sg_device_cert_file_name, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetDevCertName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}

int HAL_GetDevPrivateKeyName(char *pDevPrivateKey, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_device_privatekey_file_name) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pDevPrivateKey, '\0', maxlen);
	strncpy(pDevPrivateKey, sg_device_privatekey_file_name, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetDevPrivateKeyName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif

}

int HAL_SetDevCertName(char *pDevCert)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pDevCert) > MAX_SIZE_OF_DEVICE_CERT_FILE_NAME){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_device_cert_file_name, '\0', MAX_SIZE_OF_DEVICE_CERT_FILE_NAME);
	strncpy(sg_device_cert_file_name, pDevCert, MAX_SIZE_OF_DEVICE_CERT_FILE_NAME);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetDevCertName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}

int HAL_SetDevPrivateKeyName(char *pDevPrivateKey)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pDevPrivateKey) > MAX_SIZE_OF_DEVICE_KEY_FILE_NAME){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_device_privatekey_file_name, '\0', MAX_SIZE_OF_DEVICE_KEY_FILE_NAME);
	strncpy(sg_device_privatekey_file_name, pDevPrivateKey, MAX_SIZE_OF_DEVICE_KEY_FILE_NAME);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetDevPrivateKeyName is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}

#else	//PSK 认证方式

int HAL_GetDevSec(char *pDevSec, uint8_t maxlen)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(sg_device_secret) > maxlen){
		return QCLOUD_ERR_FAILURE;
	}

	memset(pDevSec, '\0', maxlen);
	strncpy(pDevSec, sg_device_secret, maxlen);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_GetDevSec is not implement");
	return QCLOUD_ERR_FAILURE;
#endif


}

int HAL_SetDevSec(const char *pDevSec)
{
#ifdef DEBUG_DEV_INFO_USED
	if(strlen(pDevSec) > MAX_SIZE_OF_DEVICE_SERC){
		return QCLOUD_ERR_FAILURE;
	}

	memset(sg_device_secret, '\0', MAX_SIZE_OF_DEVICE_SERC);
	strncpy(sg_device_secret, pDevSec, MAX_SIZE_OF_DEVICE_SERC);

	return QCLOUD_ERR_SUCCESS;
#else
	Log_e("HAL_SetDevSec is not implement");
	return QCLOUD_ERR_FAILURE;
#endif
}
#endif

int HAL_GetDevInfo(void *pdevInfo)
{
	int ret;
	DeviceInfo *devInfo = (DeviceInfo *)pdevInfo;		
	memset((char *)devInfo, 0, sizeof(DeviceInfo));
	ret = HAL_GetProductID(devInfo->product_id, MAX_SIZE_OF_PRODUCT_ID);
	ret |= HAL_GetDevName(devInfo->device_name, MAX_SIZE_OF_DEVICE_NAME); 
	
#ifdef 	AUTH_MODE_CERT
	ret |= HAL_GetDevCertName(devInfo->devCertFileName, MAX_SIZE_OF_DEVICE_CERT_FILE_NAME);
	ret |= HAL_GetDevPrivateKeyName(devInfo->devPrivateKeyFileName, MAX_SIZE_OF_DEVICE_KEY_FILE_NAME);
#else
	ret |= HAL_GetDevSec(devInfo->devSerc, MAX_SIZE_OF_DEVICE_SERC);
#endif 

	if(QCLOUD_ERR_SUCCESS != ret){
		Log_e("Get device info err");		
		ret = QCLOUD_ERR_DEV_INFO;
	}

	return ret;
}

