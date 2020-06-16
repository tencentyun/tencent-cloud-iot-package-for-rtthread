/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"
#include "utils_getopt.h"

#ifdef AUTH_MODE_CERT
/* NULL cert file */
#define QCLOUD_IOT_NULL_CERT_FILENAME "YOUR_DEVICE_CERT_FILE_NAME"
/* NULL key file */
#define QCLOUD_IOT_NULL_KEY_FILENAME "YOUR_DEVICE_PRIVATE_KEY_FILE_NAME"
#else
/* NULL device secret */
#define QCLOUD_IOT_NULL_DEVICE_SECRET "YOUR_IOT_PSK"
#endif
#define DYN_REG_THREAD_STACK_SIZE 8096

static uint8_t running_state = 0;

static int dyn_reg_thread(void)
{
    int        ret;
    DeviceInfo sDevInfo;
    bool       infoNullFlag = false;

    // init log level
    IOT_Log_Set_Level(eLOG_DEBUG);

    memset((char *)&sDevInfo, 0, sizeof(DeviceInfo));
    ret = HAL_GetDevInfo(&sDevInfo);
    sDevInfo.dev_type = eCOMMON_DEV;
#ifdef AUTH_MODE_CERT
    /* just demo the cert/key files are empty */
    if (!strcmp(sDevInfo.dev_cert_file_name, QCLOUD_IOT_NULL_CERT_FILENAME) ||
        !strcmp(sDevInfo.dev_key_file_name, QCLOUD_IOT_NULL_KEY_FILENAME)) {
        Log_d("dev Cert not exist!");
        infoNullFlag = true;
    } else {
        Log_d("dev Cert exist");
    }
#else
    /* just demo the PSK is empty */
    if (!strcmp(sDevInfo.device_secret, QCLOUD_IOT_NULL_DEVICE_SECRET)) {
        Log_d("dev psk not exist!");
        infoNullFlag = true;
    } else {
        Log_d("dev psk exist");
    }
#endif

    /* device cert/key files or PSK is empty, do dynamic register to fetch */
    if (infoNullFlag) {
        if (QCLOUD_RET_SUCCESS == IOT_DynReg_Device(&sDevInfo)) {
            ret = HAL_SetDevInfo(&sDevInfo);
            if (QCLOUD_RET_SUCCESS != ret) {
                Log_e("devices info save fail");
            } else {
#ifdef AUTH_MODE_CERT
                Log_d(
                    "dynamic register success, productID: %s, devName: %s, CertFile: "
                    "%s, KeyFile: %s",
                    sDevInfo.product_id, sDevInfo.device_name, sDevInfo.dev_cert_file_name, sDevInfo.dev_key_file_name);
#else
                Log_d(
                    "dynamic register success,productID: %s, devName: %s, "
                    "device_secret: %s",
                    sDevInfo.product_id, sDevInfo.device_name, sDevInfo.device_secret);
#endif
            }
        } else {
            Log_e("%s dynamic register fail", sDevInfo.device_name);
        }
    }

    return ret;
}

static int tc_dyn_reg_example(int argc, char **argv)
{
    rt_thread_t tid;
    int stack_size = DYN_REG_THREAD_STACK_SIZE;

    //init log level
    IOT_Log_Set_Level(eLOG_DEBUG);

    if (2 == argc) {
        if (!strcmp("start", argv[1])) {
            if (1 == running_state) {
                Log_d("tc_dyn_reg_example is already running\n");
                return 0;
            }
        } else if (!strcmp("stop", argv[1])) {
            if (0 == running_state) {
                Log_d("tc_dyn_reg_example is already stopped\n");
                return 0;
            }
            running_state = 0;
            return 0;
        } else {
            Log_d("Usage: tc_dyn_reg_example start/stop");
            return 0;
        }
    } else {
        Log_e("Para err, usage: tc_dyn_reg_example start/stop");
        return 0;
    }

    tid = rt_thread_create("dyn_reg_sample", (void (*)(void *))dyn_reg_thread,
                           NULL, stack_size, RT_THREAD_PRIORITY_MAX / 2 - 1, 10);

    if (tid != RT_NULL) {
        rt_thread_startup(tid);
    }

    return 0;
}


#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(tc_dyn_reg_example, startup dynamic register example);
#endif

#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(tc_dyn_reg_example, startup dynamic register example);
#endif

