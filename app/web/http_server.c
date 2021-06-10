////////////////////////////////////////////////////////////////////////////////
/// @file     http_server.c
/// @author   LiuYQ (liuyunqing@mindmotion.com.cn)
/// @version  1.0.0
/// @date     2021-04-21
/// @brief    THIS FILE PROVIDES ALL THE http_server.c EXAMPLE.
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
/// <H2><CENTER>&COPY; COPYRIGHT 2018-2021 MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion  --------------------------------------
#define _HTTP_SERVER_C_

// Includes  -------------------------------------------------------------------
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "lwip/arch.h"
#include "lwip/opt.h"
#include "lwip/tcpbase.h"
#include "lwip/tcp.h"

#include "FreeRTOS.h"
#include "timers.h"

#include "http_server.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Appliaction_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Appliaction_Http
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Appliaction_Http_Data
/// @{

const HtmlServerRouter_TypeDef httpRouter[] = {
    {"/",                   "/index.html"},
    {"/favicon.ico",        "/asset/favicon.ico"},
    {"/js/main.js",         "/js/main.js"},
    {"/css/style.css",      "/css/style.css"},
    {"/css/asset/off.png",  "/asset/off.png"},
    {"/css/asset/on.png",   "/asset/on.png"},

    {"*",                   "/404.html"}
};

/// @}

#if defined(LWIP_NETCONN) && (LWIP_NETCONN == 1)
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Http_Server_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Http server post processing function.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void http_post_btn_process(const char * url, const char * body)
{
    if (strstr(body, "true") == NULL) {
        buttonClickedFlag = false;
    } else {
        buttonClickedFlag = true;
    }

    xSemaphoreGive(s_xBtnSemaphore);
}

void SendFile(const char * path)
{
    struct fs_file file;
    err_t error = ERR_OK;

    error = fs_open(&file, path);

    if (error == ERR_OK) {
        netconn_write(httpActiveConnection, (const unsigned char *)(file.data),
          (size_t)file.len, NETCONN_NOCOPY);
    } else {
        printf("[ERROR] SendFile File read failed, path: %s, error code: %d\n", path, error);
    }

    fs_close(&file);
}

err_t TrySendFile(const char * path)
{
    struct fs_file file;
    err_t error = ERR_OK;

    error = fs_open(&file, path);

    if (error == ERR_OK) {
        netconn_write(httpActiveConnection, (const unsigned char *)(file.data),
          (size_t)file.len, NETCONN_NOCOPY);
    } else {
        printf("[LOG] TrySendFile read failed, path: %s, error code: %d\n", path, error);
    }

    fs_close(&file);

    return error;
}

void SerchSendFile(const char * url)
{
    static uint16_t routerLength = sizeof (httpRouter) / sizeof (HtmlServerRouter_TypeDef);
    uint16_t i = 0;

    for (i = 0; i < routerLength; i++) {
        if (!strcmp (url, httpRouter[i].url)) {
            SendFile(httpRouter[i].path);
            break;
        }
    }

    // Send 404.
    if (i >= routerLength) {
        printf("[WARNING] Not found path %s, Sended 404 page.\n", url);
        SendFile(httpRouter[routerLength - 1].path);
    }
}

void ProcessHttpGet (const char * url, const char * body)
{
    err_t error = ERR_OK;

    error = TrySendFile(url);

    if (error == ERR_OK) {
        return;
    }

    SerchSendFile(url);
}

void ProcessHttpPost (const char * url, const char * body)
{
    if (!strcmp(url, "/button_clicked")) {
        http_post_btn_process(url, body);
        TrySendFile("/asset/ok.json");
    }
}

void ProcessHttpRequest (const char * request, uint16_t length)
{
    char * mem = NULL;
    char * str = NULL;
    char * body = NULL;
    char * url = NULL;

    mem = malloc(length);
    memset(mem, 0, length);

    str = mem;
    body = mem;

    memcpy(str, request, sizeof(char) * length);

    HtmlRequestMethod_TypeDef method = HTTP_UNKNOWN;

    // Get Http Request Method
    if (str != NULL) {
        str = strtok(str, " ");
        if (!strcmp (str, "GET")) {
            method = HTTP_GET;
            printf("[LOG] Method: GET\n");
        } else if (!strcmp (str, "POST")) {
            method = HTTP_POST;
            printf("[LOG] Method: POST\n");
        } else {
            method = HTTP_UNKNOWN;
            printf("[LOG] Method: Unknown\n");
        }
    }

    // Get URL
    if (str != NULL) {
        str = strtok(NULL, " ");

        if (str != NULL) {
            url = malloc(strlen(str) + 1);
            memset(url, 0, strlen(str) + 1);
            strcpy(url, str);

            printf("[LOG] URL: %s\n", url);
        }
    }

    memcpy(body, request, sizeof(char) * length);


    // Process Http Request
    switch (method) {
    case HTTP_GET:
        ProcessHttpGet(url, body);
        break;
    case HTTP_POST:
        ProcessHttpPost(url, body);
        break;
    default:
        break;
    }

    free(url);
    free(mem);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Http server task processing function.
/// @param  arg: Task parameters.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void http_server_process(struct netconn * conn)
{

    struct netbuf * inbuf;
    char *          buf;
    u16_t           buflen;

    // Receive connection data.
    if (netconn_recv(conn, &inbuf) == ERR_OK) {

        // Get and reset pending error on the connection.
        if (netconn_err(conn) == ERR_OK) {

            // Get data and data length.
            netbuf_data(inbuf, (void **)&buf, &buflen);

            ProcessHttpRequest (buf, buflen);
        }
    }

    // Close the connection (server closes in HTTP)
    netconn_close(conn);

    // Delete the buffer (netconn_recv gives us ownership,
    // so we have to make sure to deallocate the buffer)
    netbuf_delete(inbuf);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Http server thread function.
/// @param  arg: Task parameters.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void http_server_thread(void * arg)
{
    struct netconn *conn, *newconn;

    LWIP_UNUSED_ARG(arg);

    conn = netconn_new(NETCONN_TCP);  // Create a new TCP connection handle.

    if (conn != NULL) {
        if (netconn_bind(conn, IP4_ADDR_ANY, HTTP_SERVER_PORT) ==
            ERR_OK) {  // Bind to port 80 (HTTP) with default IP address

            netconn_listen(conn);  // Start listening port.

            while (1) {
                // Accept a new connection on a TCP listening connection.
                if (netconn_accept(conn, &newconn) == ERR_OK) {
                    if (newconn == NULL) {
                        printf("[ERROR]");
                    }

                    httpActiveConnection = newconn;
                    http_server_process(newconn);  // Processing connection

                    httpActiveConnection = NULL;
                    netconn_delete(newconn);       // Close the connection
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Http server task creation function.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void http_server_init(void)
{
    sys_thread_new("HTTP_SERVER", http_server_thread, NULL, 128, 2);
}

#endif

/// @}

/// @}

/// @}
