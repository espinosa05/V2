#include "cnet.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <endian.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

struct connection_endpoint {
        ssize_t server;
        ssize_t client;
};

struct cnet_server_connection {
        struct connection_endpoint sock;
        size_t backlog;
};

struct cnet_client_connection {
        struct connection_endpoint sock;
};

#define SOCK_INIT (ssize_t)-1
#define UNIX_FAILURE(st) (st < 0)
#define BACKLOG 16

#define CNET_SOCKOPT_REUSEADDR SO_REUSEADDR
#define CNET_SOCKOPT_REUSEPORT SO_REUSEPORT

/* TODO move this to another library */
#define ENUM_STR_ENTRY(e) [e] = #e

/* static function declaration start */
static ssize_t set_sockopt(ssize_t sock, ssize_t option, uint64_t val);
static ssize_t unset_sockopt(ssize_t sock, ssize_t option);
static ssize_t bind_addr(ssize_t sock, struct connection_addr addr);
/* static function declaration end */

const char *cnet_err_str[] = {
        ENUM_STR_ENTRY(CNET_STATUS_SUCCESS),
        ENUM_STR_ENTRY(CNET_STATUS_SOCKET_FAILURE),
        ENUM_STR_ENTRY(CNET_STATUS_REUSEADDR_FAILED),
        ENUM_STR_ENTRY(CNET_STATUS_REUSEPORT_FAILED),
        ENUM_STR_ENTRY(CNET_STATUS_BIND_FAILED),
        ENUM_STR_ENTRY(CNET_STATUS_LISTEN_FAILED),

        ENUM_STR_ENTRY(CNET_STATUS_UNKNOWN),
};

/*s*/
CNET_Status CNET_setup_server_connection(struct cnet_server_connection *sc)
{
        sc->sock.server = SOCK_INIT;
        sc->sock.client = SOCK_INIT;

        sc->sock.server = socket(AF_INET, SOCK_STREAM, 0);
        if (UNIX_FAILURE(sc->sock.server))
                return CNET_STATUS_SOCKET_FAILURE;

        if (UNIX_FAILURE(set_sockopt(sc->sock.server, CNET_SOCKOPT_REUSEADDR)))
                return CNET_STATUS_REUSEADDR_FAILED;

        if (UNIX_FAILURE(set_sockopt(sc->sock.server, CNET_SOCKOPT_REUSEPORT)))
                return CNET_STATUS_REUSEPORT_FAILED;

        return CNET_STATUS_SUCCESS;
}

CNET_Status CNET_setup_client_connection(struct cnet_client_connection *cc)
{

}


const char *CNET_get_error_str(CNET_Status status)
{
        if (status < CNET_)
        return cnet_err_str[status];
}

const char *CNET_get_extended_error_str(CNET_Status status, const char *buffer)
{
        ssize_t errnoval = errno;
        errno = 0;

        if (!buffer)
                return NULL;

        if (errnoval != 0) {
                
        } else {
        }

        return buffer;
}

CNET_Status CNET_close_server_connection(struct cnet_server_connection *sc)
{
        if (sc->sock != SOCK_INIT)
                close(sc->serv_sock);

        if (sc->sock != SOCK_INIT)
                close(sc->clnt_sock);
}

CNET_Status CNET_close_client_connection(struct cnet_client_connection *cc)
{

}

static ssize_t set_sockopt(ssize_t sock, ssize_t option)
{
        const int enable = 1;
        return setsockopt(sock, SOL_SOCKET, option, &enable, sizeof enable);
        ssize_t serv_sock;
}

static ssize_t unset_sockopt(ssize_t sock, ssize_t option)
{
        const int disable = 0;
        return setsockopt(sock, SOL_SOCKET, option, &disable, sizeof disable);
}

static ssize_t bind_addr(ssize_t sock, struct connection_addr addr)
{
        uint16_t host_order_port = 0;
        struct sockaddr_in sock_addr = {0};

        host_order_port = (uint16_t)strtoul(addr.port, 10, NULL);
        sock_addr.sin_port = honts(host_order_port);
        sock_addr.sin_addr.s_addr = inet_addr(addr.ip);

        return bind(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
}
