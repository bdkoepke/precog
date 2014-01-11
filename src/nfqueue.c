#include <stdio.h>
#include <stdlib.h>
#include "nfqueue.h"

#define NETFILTER_ERROR g_quark_from_static_string("NETFILTER_ERROR")
#define NETFILTER_ERROR_INIT 0

struct nfq_handle*
nfq_handle_new(GError** error)
{
	struct nfq_handle *handle = nfq_open();
	if (!handle)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "during nfq_open()");
		return NULL;
	}
	if (nfq_unbind_pf(handle, AF_INET) < 0)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "during nfq_unbind_pf()");
		return NULL;
	}
	return handle;
}

struct nfq_q_handle*
nfq_q_handle_new(struct nfq_handle* handle,
				 queue_callback_t callback,
				 GError** error)
{
	if (!handle)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "handle is null");
		return NULL;
	}
	if (!callback)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "callback is null");
		return NULL;
	}

	struct nfq_q_handle *queue = nfq_create_queue(handle, 0, callback, NULL);
	if (!queue)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "during nfq_create_queue()");
		return NULL;
	}
	if (nfq_set_mode(queue, NFQNL_COPY_PACKET, 0xffff) < 0)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "can't set packet copy mode");
		return NULL;
	}
	return queue;
}

size_t
nfqueue_fd_new(struct nfq_handle *handle,
			   GError** error)
{
	if (!handle)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "handle is null");
		return 0;
	}
	struct nfnl_handle *netlink_handle = nfq_nfnlh(handle);
	if (!netlink_handle)
	{
		g_set_error(error, NETFILTER_ERROR, NETFILTER_ERROR_INIT, "netlink_handle is null");
		return 0;
	}
	return nfnl_fd(netlink_handle);
}
