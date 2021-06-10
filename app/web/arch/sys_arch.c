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

#define _SYS_ARCH_C_

#include <string.h>

#include "lwip/tcpip.h"

#include "sys_arch.h"

u32_t sys_jiffies(void)
{
    lwip_sys_now = xTaskGetTickCount();
    return lwip_sys_now;
}

u32_t sys_now(void)
{
    lwip_sys_now = xTaskGetTickCount();
    return lwip_sys_now;
}

void sys_init(void)
{
    lwip_sys_mutex = xSemaphoreCreateMutex();
}

SysTimouts_TypeDef* sys_arch_timeouts(void)
{
    int i;
    xTaskHandle pid;
    struct timeoutlist* tl;
    pid = xTaskGetCurrentTaskHandle();
    for(i = 0; i < s_nextthread; i++) {
        tl = &(s_timeoutlist[i]);
        if(tl->pid == pid) {
            return &(tl->timeouts);
        }
    }
    return NULL;
}

sys_prot_t sys_arch_protect(void)
{
    xSemaphoreTake(lwip_sys_mutex, portMAX_DELAY);
    return 1;
}

void sys_arch_unprotect(sys_prot_t pval)
{
    ( void ) pval;
    xSemaphoreGive(lwip_sys_mutex);
}

err_t sys_sem_new(sys_sem_t* sem, u8_t count)
{
    SemaphoreHandle_t sema;
    vSemaphoreCreateBinary(sema);
    *sem = sema;

    if(*sem == NULL) {
#if SYS_STATS
        ++lwip_stats.sys.sem.err;
#endif /* SYS_STATS */
        return ERR_MEM;
    }

    if(count == 0) {
        xSemaphoreTake(*sem, portMAX_DELAY);
    }

#if SYS_STATS
    ++lwip_stats.sys.sem.used;
    if (lwip_stats.sys.sem.max < lwip_stats.sys.sem.used) {
        lwip_stats.sys.sem.max = lwip_stats.sys.sem.used;
    }
#endif /* SYS_STATS */

    return ERR_OK;
}

void sys_sem_free(sys_sem_t* sem)
{
#if SYS_STATS
    --lwip_stats.sys.sem.used;
#endif /* SYS_STATS */

    vSemaphoreDelete(*sem);
    *sem = SYS_SEM_NULL;
}


int sys_sem_valid(sys_sem_t* sem)
{
    return (*sem != SYS_SEM_NULL);
}


void sys_sem_set_invalid(sys_sem_t* sem)
{
    *sem = SYS_SEM_NULL;
}


u32_t sys_arch_sem_wait(sys_sem_t* sem, u32_t timeout)
{
    u32_t wait_tick = 0;
    u32_t start_tick = 0 ;


    if(*sem == SYS_SEM_NULL) {
        return SYS_ARCH_TIMEOUT;
    }

    start_tick = xTaskGetTickCount();

    //timeout != 0
    if(timeout != 0) {
        wait_tick = timeout / portTICK_PERIOD_MS;
        if (wait_tick == 0) {
            wait_tick = 1;
        }
    } else {
        wait_tick = portMAX_DELAY;
    }

    if(xSemaphoreTake(*sem, wait_tick) == pdTRUE) {
        return ((xTaskGetTickCount() - start_tick) * portTICK_RATE_MS);
    } else {
        return SYS_ARCH_TIMEOUT;
    }
}

void sys_sem_signal(sys_sem_t* sem)
{
    xSemaphoreGive( *sem );
}

err_t sys_mutex_new(sys_mutex_t* mutex)
{
    //create  sem
    *mutex = xSemaphoreCreateMutex();
    if(*mutex != SYS_MRTEX_NULL) {
        return ERR_OK;
    } else {
#if defined(USER_DEBUG)
        printf("[sys_arch]:new mutex fail!\n");
#endif
        return ERR_MEM;
    }
}

void sys_mutex_free(sys_mutex_t* mutex)
{
    vSemaphoreDelete(*mutex);
}

void sys_mutex_set_invalid(sys_mutex_t* mutex)
{
    *mutex = SYS_MRTEX_NULL;
}

void sys_mutex_lock(sys_mutex_t* mutex)
{
    xSemaphoreTake(*mutex, portMAX_DELAY);
}

void sys_mutex_unlock(sys_mutex_t* mutex)
{
    xSemaphoreGive( *mutex );
}


sys_thread_t sys_thread_new(const char* name, lwip_thread_fn function, void* arg, int stacksize, int prio)
{
    sys_thread_t handle = NULL;
    BaseType_t xReturn = pdPASS;

    xReturn = xTaskCreate((TaskFunction_t )function,   // Task entry function
                          (const char*    )name, // Task name
                          (uint16_t       )stacksize,   // Task stack size
                          (void*          )arg, // Task entry function parameters
                          (UBaseType_t    )prio,  // The priority of the task
                          (TaskHandle_t*  )&handle); // Task control block pointer
    if(xReturn != pdPASS) {
#if defined(USER_DEBUG)
        printf("[ERROR] sys_arch: create task fail!err:%#lx\n", xReturn);
#endif
        return NULL;
    }

    return handle;
}

err_t sys_mbox_new(sys_mbox_t* mbox, int size)
{

    *mbox = xQueueCreate((UBaseType_t ) size,
                         (UBaseType_t ) sizeof(void*));
#if SYS_STATS
    ++lwip_stats.sys.mbox.used;
    if (lwip_stats.sys.mbox.max < lwip_stats.sys.mbox.used) {
        lwip_stats.sys.mbox.max = lwip_stats.sys.mbox.used;
    }
#endif /* SYS_STATS */
    if(*mbox == NULL) {
        return ERR_MEM;
    }

    return ERR_OK;
}

void sys_mbox_free(sys_mbox_t* mbox)
{
    if( uxQueueMessagesWaiting( *mbox ) ) {
        /* Line for breakpoint.  Should never break here! */
        portNOP();
#if SYS_STATS
        lwip_stats.sys.mbox.err++;
#endif /* SYS_STATS */

        // TODO notify the user of failure.
    }

    vQueueDelete(*mbox);

#if SYS_STATS
    --lwip_stats.sys.mbox.used;
#endif /* SYS_STATS */
}

int sys_mbox_valid(sys_mbox_t* mbox)
{
    if (*mbox == SYS_MBOX_NULL) {
        return 0;
    } else {
        return 1;
    }
}

void sys_mbox_set_invalid(sys_mbox_t* mbox)
{
    *mbox = SYS_MBOX_NULL;
}

void sys_mbox_post(sys_mbox_t* q, void* msg)
{
    while(xQueueSend( *q, &msg,portMAX_DELAY) != pdTRUE);
}

err_t sys_mbox_trypost(sys_mbox_t* q, void* msg)
{
    if(xQueueSend(*q, &msg, 1) == pdPASS) {
        return ERR_OK;
    } else {
        return ERR_MEM;
    }
}

err_t sys_mbox_trypost_fromisr(sys_mbox_t* q, void* msg)
{
    return sys_mbox_trypost(q, msg);
}

u32_t sys_arch_mbox_fetch(sys_mbox_t* q, void** msg, u32_t timeout)
{
    BaseType_t xEntryTimeSet = pdFALSE;
    uint32_t starttime = xTaskGetTickCount();

    if(timeout != 0) {
        xEntryTimeSet = xQueueReceive(*q, msg, timeout / portTICK_PERIOD_MS);
    } else {
        xEntryTimeSet = xQueueReceive(*q, msg, portMAX_DELAY);
    }

    if (xEntryTimeSet == pdTRUE) {
        return xTaskGetTickCount() - starttime;
    } else {
        return SYS_ARCH_TIMEOUT;
    }
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t* q, void** msg)
{
    void* dummyptr;
    if ( msg == NULL ) {
        msg = &dummyptr;
    }

    if(xQueueReceive(*q, &(*msg), 0) == pdTRUE) {
        return ERR_OK;
    } else {
        return SYS_MBOX_EMPTY;
    }
}

#if LWIP_NETCONN_SEM_PER_THREAD
    #error LWIP_NETCONN_SEM_PER_THREAD==1 not supported
#endif /* LWIP_NETCONN_SEM_PER_THREAD */
