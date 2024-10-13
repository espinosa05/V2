#ifndef __LIB_C_NET_H__
#define __LIB_C_NET_H__

#include <stdint.h>

struct cnet_server_connection;
struct cnet_client_connection;

struct connection_addr {
        const char *addr;
        const char *port;
};

typedef size_t CNET_Status;

enum cnet_status_codes {
        CNET_STATUS_SUCCESS = 0,
        CNET_STATUS_SOCKET_FAILURE,
        CNET_STATUS_REUSEADDR_FAILED,
        CNET_STATUS_REUSEPORT_FAILED,
        CNET_STATUS_BIND_FAILED,
        CNET_STATUS_LISTEN_FAILED,
        CNET_STATUS_N_ERR,
#define CNET_STATUS_UNKNOWN CNET_STATUS_N_ERR
};

/* initialize connection data */
CNET_Status CNET_setup_server_connection(struct cnet_server_connection *sc);
CNET_Status CNET_setup_client_connection(struct cnet_client_connection *cc);

/* wait for incoming client connection requests */
CNET_Status CNET_listen(struct cnet_server_connection *sc);
/* connect to a server */
CNET_Status CNET_connect(struct cnet_client_connection *cc, struct connection_addr *addr);

const char *CNET_get_error_str(CNET_Status status, const char **buffer);
CNET_Status CNET_close_server_connection(struct cnet_server_connection *sc);
CNET_Status CNET_close_client_connection(struct cnet_client_connection *cc);

#endif /* __LIB_C_NET_H__ */
