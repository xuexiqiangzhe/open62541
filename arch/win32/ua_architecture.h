/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2016-2017 (c) Julius Pfrommer, Fraunhofer IOSB
 *    Copyright 2017 (c) Stefan Profanter, fortiss GmbH
 */

#ifndef PLUGINS_ARCH_WIN32_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_WIN32_UA_ARCHITECTURE_H_

#ifndef _BSD_SOURCE
# define _BSD_SOURCE
#endif

/* Disable some security warnings on MSVC */
#ifdef _MSC_VER
# define _CRT_SECURE_NO_WARNINGS
#endif

/* Assume that Windows versions are newer than Windows XP */
#if defined(__MINGW32__) && (!defined(WINVER) || WINVER < 0x501)
# undef WINVER
# undef _WIN32_WINDOWS
# undef _WIN32_WINNT
# define WINVER 0x0501
# define _WIN32_WINDOWS 0x0501
# define _WIN32_WINNT 0x0501
#endif

/* Backup definition of SLIST_ENTRY on mingw winnt.h */
#ifdef SLIST_ENTRY
# pragma push_macro("SLIST_ENTRY")
# undef SLIST_ENTRY
# define POP_SLIST_ENTRY
#endif


#include <stdlib.h>
#if defined(_WIN32) && !defined(__clang__)
# include <malloc.h>
#endif

#include <stdio.h>
#include <errno.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#ifdef _MSC_VER
# ifndef UNDER_CE
#  include <io.h> //access
#  define UA_access _access
# endif
#else
# include <unistd.h> //access and tests
# define UA_access access
#endif



#ifdef POP_SLIST_ENTRY
# undef SLIST_ENTRY
# undef POP_SLIST_ENTRY
# pragma pop_macro("SLIST_ENTRY")
#endif

#define ssize_t int
#define OPTVAL_TYPE char
#define UA_sleep_ms(X) Sleep(X)

#define UA_fd_set(fd, fds) FD_SET((unsigned int)fd, fds)
#define UA_fd_isset(fd, fds) FD_ISSET((unsigned int)fd, fds)

#ifdef UNDER_CE
# define errno
#endif

#define UA_IPV6 1
#define UA_SOCKET int
#define UA_INVALID_SOCKET -1
#define UA_ERRNO WSAGetLastError()
#define UA_INTERRUPTED WSAEINTR
#define UA_AGAIN WSAEWOULDBLOCK
#define UA_EAGAIN EAGAIN
#define UA_WOULDBLOCK WSAEWOULDBLOCK
#define UA_ERR_CONNECTION_PROGRESS WSAEWOULDBLOCK

#define UA_getnameinfo getnameinfo
#define UA_send send
#define UA_recv recv
#define UA_close closesocket
#define UA_select select
#define UA_shutdown shutdown
#define UA_socket socket
#define UA_bind bind
#define UA_listen listen
#define UA_accept accept
#define UA_connect connect
#define UA_getaddrinfo getaddrinfo
#define UA_getsockopt getsockopt
#define UA_setsockopt setsockopt
#define UA_freeaddrinfo freeaddrinfo
#define UA_gethostname gethostname

#define UA_free free
#define UA_malloc malloc
#define UA_calloc calloc
#define UA_realloc realloc

#define UA_snprintf(source, size, string, ...) _snprintf_s(source, size, _TRUNCATE, string, __VA_ARGS__)

#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { \
    char *errno_str = NULL; \
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
    NULL, WSAGetLastError(), \
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
    (LPSTR)&errno_str, 0, NULL); \
    LOG; \
    LocalFree(errno_str); \
}
#define UA_LOG_SOCKET_ERRNO_GAI_WRAP UA_LOG_SOCKET_ERRNO_WRAP

#include "../ua_architecture_functions.h"

#endif /* PLUGINS_ARCH_WIN32_UA_ARCHITECTURE_H_ */
