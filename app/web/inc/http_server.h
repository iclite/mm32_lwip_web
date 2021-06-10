////////////////////////////////////////////////////////////////////////////////
/// @file     http_server.h
/// @author   LiuYQ (liuyunqing@mindmotion.com.cn)
/// @version  v2.0.0
/// @date     2019-08-02
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE http_server.h EXAMPLES.
/// ////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2019 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#ifndef __HTTP_SERVER_H
#define __HTTP_SERVER_H

#include <stdbool.h>

#define HTTP_SERVER_PORT                80

typedef enum {
    HTTP_POST,
    HTTP_GET,
    HTTP_UNKNOWN,
} HtmlRequestMethod_TypeDef;

typedef struct {
    const char * url;
    const char * path;
} HtmlServerRouter_TypeDef;

////////////////////////////////////////////////////////////////////////////////
#ifdef _HTTP_SERVER_C_
#define GLOBAL

static struct netconn *httpActiveConnection = NULL;

GLOBAL sys_sem_t s_xBtnSemaphore = NULL;
GLOBAL bool buttonClickedFlag = false;

#else
#define GLOBAL extern
#endif

GLOBAL sys_sem_t s_xBtnSemaphore;

GLOBAL bool buttonClickedFlag;

#undef GLOBAL

////////////////////////////////////////////////////////////////////////////////
void http_server_init(void);

#endif
