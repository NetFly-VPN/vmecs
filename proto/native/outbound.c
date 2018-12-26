#include "outbound.h"
#include "tcp.h"

static tcp_socket_t *
_native_tcp_outbound_client(tcp_outbound_t *_outbound, const target_id_t *target)
{
    tcp_socket_t *sock = (tcp_socket_t *)native_tcp_socket_new();
    
    if (tcp_socket_connect_target(sock, target)) {
        tcp_socket_close(sock);
        tcp_socket_free(sock);
        return NULL;
    }

    return sock;
}

static tcp_socket_t *
_native_tcp_outbound_socket(tcp_outbound_t *_outbound, const target_id_t *target)
{
    return (tcp_socket_t *)native_tcp_socket_new();
}

static int
_native_tcp_outbound_try_connect(tcp_outbound_t *_outbound, tcp_socket_t *sock, const target_id_t *target)
{
    return tcp_socket_try_connect_target(sock, target);
}

static void
_native_tcp_outbound_free(tcp_outbound_t *outbound)
{
    if (outbound) {
        free(outbound);
    }
}

native_tcp_outbound_t *
native_tcp_outbound_new()
{
    native_tcp_outbound_t *ret = malloc(sizeof(*ret));
    ASSERT(ret, "out of mem");

    ret->client_func = _native_tcp_outbound_client;
    ret->socket_func = _native_tcp_outbound_socket;
    ret->try_connect_func = _native_tcp_outbound_try_connect;
    ret->free_func = _native_tcp_outbound_free;
    
    return ret;
}
