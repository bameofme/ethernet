#include <stdio.h>
#include <netlink/socket.h>
#include <netlink/netlink.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <errno.h>

#include "../my_gen_netlink.h"

#define prerr(...) fprintf(stderr, "error: " __VA_ARGS__)

/* Allocate netlink socket and connect to generic netlink */
int conn(struct nl_sock **sk)
{
	*sk = nl_socket_alloc();
	if (!sk) {
		return -ENOMEM;
	}

	return genl_connect(*sk);
}
/* Disconnect and release socket */
void disconn(struct nl_sock *sk)
{
	nl_close(sk);
	nl_socket_free(sk);
}