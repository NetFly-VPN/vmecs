#ifndef _PROTO_RELAY_OUTBOUND_H_
#define _PROTO_RELAY_OUTBOUND_H_

#include "pub/type.h"

#include "proto/tcp.h"
#include "proto/common.h"

// a outbound acts like a client

#define TCP_OUTBOUND_HEADER \
    tcp_outbound_client_t client_func; \
    tcp_outbound_socket_t socket_func; \
    tcp_outbound_try_connect_t try_connect_func; \
    tcp_outbound_free_t free_func;

struct tcp_outbound_t_tag;

typedef tcp_socket_t *(*tcp_outbound_client_t)(struct tcp_outbound_t_tag *outbound, const target_id_t *target);
typedef tcp_socket_t *(*tcp_outbound_socket_t)(struct tcp_outbound_t_tag *outbound, const target_id_t *target);
typedef int (*tcp_outbound_try_connect_t)(struct tcp_outbound_t_tag *outbound, tcp_socket_t *sock, const target_id_t *target);
typedef void (*tcp_outbound_free_t)(struct tcp_outbound_t_tag *outbound);

typedef struct tcp_outbound_t_tag {
    TCP_OUTBOUND_HEADER
} tcp_outbound_t;

INLINE tcp_socket_t *
tcp_outbound_client(void *outbound, const target_id_t *target)
{
    return ((tcp_outbound_t *)outbound)->client_func(outbound, target);
}

INLINE tcp_socket_t *
tcp_outbound_socket(void *outbound, const target_id_t *target)
{
    return ((tcp_outbound_t *)outbound)->socket_func(outbound, target);
}

INLINE int
tcp_outbound_try_connect(void *outbound, tcp_socket_t *sock, const target_id_t *target)
{
    return ((tcp_outbound_t *)outbound)->try_connect_func(outbound, sock, target);
}

INLINE void
tcp_outbound_free(void *outbound)
{
    if (outbound) {
        ((tcp_outbound_t *)outbound)->free_func(outbound);
    }
}

#endif
