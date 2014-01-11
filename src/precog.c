/*
 * Copyright (C) 2014 Brandon Koepke <bdkoepke@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "nfqueue.h"

#include <arpa/inet.h>
#include <assert.h>
#include <glib.h>
#include <libnetfilter_queue/libnetfilter_queue_ipv4.h>
#include <libnetfilter_queue/libnetfilter_queue_tcp.h>
#include <linux/ip.h>
#include <linux/netfilter.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int
queue_callback(struct nfq_q_handle *queue,
			   struct nfgenmsg *message,
			   struct nfq_data *nfa,
			   void *user_data)
{
	struct nfqnl_msg_packet_hdr *packet_header = nfq_get_msg_packet_hdr(nfa);
	if (packet_header == NULL) return -1;

	uint8_t *buffer;
	nfq_get_payload(nfa, &buffer);
	struct iphdr *ip_info = (struct iphdr*) (buffer);

	int id = ntohl(packet_header->packet_id);
	if (ip_info->protocol == IPPROTO_ICMP &&
		ip_info->saddr == 0x0800a8c0)
	{
		printf("icmp drop from %p %d\n",  ip_info->daddr, id);
		nfq_set_verdict(queue, id, NF_DROP, 0, NULL);
		return id;
	}
	printf("accept %d\n", id);
	nfq_set_verdict(queue, id, NF_ACCEPT, 0, NULL);
	return id;
}

void
run(queue_callback_t callback, GError** error)
{
	if (*error) return;
	struct nfq_handle *handle = nfq_handle_new(error);
	if (! *error)
	{
		struct nfq_q_handle *queue = nfq_q_handle_new(handle, callback, error);
		if (! *error)
		{
			size_t nfqueue_fd = nfqueue_fd_new(handle, error);
			if (! *error)
			{
				uint8_t buffer[4096];
				for (;;)
				{
					int received = recv(nfqueue_fd, buffer, sizeof (buffer), 0);
					if (received == -1)
						break;
					nfq_handle_packet(handle, (char*)buffer, received);
				}
			}
			nfq_close(handle);
		}
		nfq_destroy_queue(queue);
	}

}

/**
 * @author Brandon Koepke <bdkoepke@gmail.com>
 */
int
main(int argc, char** argv)
{
	GError* error;
	run(queue_callback, &error);
	if (error)
	{
		perror(error->message);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
