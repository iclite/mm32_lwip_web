/*
 * Copyright (c) 2017 Simon Goldschmidt
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Simon Goldschmidt
 *
 */

#ifndef __SYS_ARCH_H
#define __SYS_ARCH_H

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

typedef struct sys_timeouts {
    struct sys_timeo* next;
} SysTimouts_TypeDef;

typedef struct timeoutlist {
    struct sys_timeouts timeouts;
    xTaskHandle pid;
} TimeoutList_TypeDef;

#define SYS_MBOX_NULL                   (QueueHandle_t)NULL
#define SYS_SEM_NULL                    (SemaphoreHandle_t)NULL
#define SYS_MRTEX_NULL                  (SemaphoreHandle_t)NULL
#define SYS_DEFAULT_THREAD_STACK_DEPTH  configMINIMAL_STACK_SIZE

#define SYS_THREAD_MAX                  4

typedef SemaphoreHandle_t               sys_sem_t;
typedef SemaphoreHandle_t               sys_mutex_t;
typedef QueueHandle_t                   sys_mbox_t;
typedef TaskHandle_t                    sys_thread_t;

#ifdef _SYS_ARCH_C_
#define GLOBAL

GLOBAL TimeoutList_TypeDef s_timeoutlist[SYS_THREAD_MAX];
GLOBAL u16_t               s_nextthread = 0;

#else
#define GLOBAL extern

#endif

GLOBAL uint32_t     lwip_sys_now;
GLOBAL sys_mutex_t  lwip_sys_mutex;

#undef GLOBAL

#endif /* __SYS_ARCH_H__ */
