#pragma once

#include <sdkconfig.h>

#ifdef ARDUINO_ARCH_ESP32
    #include "esp32-hal-log.h"
#endif

#ifndef CONFIG_BL_HANDLER_LOG_TAG
#define CONFIG_BL_HANDLER_LOG_TAG                 "BLHANDLER"
#endif /* CONFIG_BL_HANDLER_LOG_TAG */
#define BLHANDLERTAG CONFIG_BL_HANDLER_LOG_TAG

#ifndef CONFIG_BL_HANDLER_TASK_PRIO
#define CONFIG_BL_HANDLER_TASK_PRIO               1                       // default task Priority 1
#endif /* CONFIG_BL_HANDLER_TASK_PRIO */

#ifndef CONFIG_BL_HANDLER_TASK_NAME
#define CONFIG_BL_HANDLER_TASK_NAME               "BLHANDLERTASK"       // default task tag name
#endif /* CONFIG_BL_HANDLER_TASK_NAME */

#ifndef CONFIG_BL_HANDLER_TASK_STACK
#define CONFIG_BL_HANDLER_TASK_STACK               (4096)                 // 4KB task memory alloc
#endif /* CONFIG_BL_HANDLER_TASK_STACK */