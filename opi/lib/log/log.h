// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __LOG_H__
#define __LOG_H__

#include <stdint.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log level
 *
 */
typedef enum {
    LOG_NONE = 0,       /*!< No log output */
    LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    LOG_INFO,       /*!< Information messages which describe normal flow of events */
    LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} log_level_t;
extern void setLogLevelGlobal(log_level_t level);
extern void _log(const char *tag, log_level_t level, const char * format, va_list list);
extern void LOGE(const char *tag,const char *format,...);
extern void LOGI(const char *tag,const char *format,...);
extern void LOGW(const char *tag,const char *format,...);
extern void VERB(const char *tag,const char *format,...);
extern void DBG(const char *tag,const char *format,...);

#endif /* __ESP_LOG_H__ */
