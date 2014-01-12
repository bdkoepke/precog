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
#include "precog.h"
#include "net/ip/ip.h"
#include "net/tcp/tcp.h"
#include "net/udp/udp.h"

#include <arpa/inet.h>
#include <assert.h>
#include <glib.h>
#include <libnetfilter_queue/libnetfilter_queue_ipv4.h>
#include <libnetfilter_queue/libnetfilter_queue_tcp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <asm/byteorder.h>

int
queue_callback(struct nfq_q_handle *queue,
			   struct nfgenmsg *message,
			   struct nfq_data *nfa,
			   void *user_data)
{
	struct nfqnl_msg_packet_hdr *packet_header = nfq_get_msg_packet_hdr(nfa);
	if (packet_header == NULL) return -1;

	uint8_t *buffer;
	const size_t length = nfq_get_payload(nfa, &buffer);
	size_t offset = 0;
	int packet_number = ntohl(packet_header->packet_id);

	GError* error = NULL;
	const ip_header_t* ip_header = ip_header_from(buffer, &offset, length, &error);
	const ip_protocol_t ip_protocol = ip_header_protocol(ip_header);

	uint16_t sport;
	uint16_t dport;
	if (ip_protocol == ip_protocol_tcp)
	{
		const tcp_header_t* tcp_header = tcp_header_from(buffer, &offset, length, &error);
		sport = tcp_header_sport(tcp_header);
		dport = tcp_header_dport(tcp_header);
	}
	else if (ip_protocol == ip_protocol_udp)
	{
		const udp_header_t* udp_header = udp_header_from(buffer, &offset, length, &error);
		sport = udp_header_sport(udp_header);
		dport = udp_header_dport(udp_header);
	}
	else if (ip_protocol == ip_protocol_icmp)
	{
		puts("icmp protocol");
		nfq_set_verdict(queue, packet_number, NF_ACCEPT, 0, NULL);
		return packet_number;
	}
	else
	{
		printf("unknown ip_protocol: %d\n", ip_protocol);
		nfq_set_verdict(queue, packet_number, NF_DROP, 0, NULL);
		return packet_number;
	}

	printf("sport: %d, dport: %d\n", sport, dport);
	uint32_t verdict = (dport == 53 || dport == 80 || dport == 443) ? NF_ACCEPT : NF_DROP;
	nfq_set_verdict(queue, packet_number, verdict, 0, NULL);
	return packet_number;

	/*
	struct iphdr *ip_info = (struct iphdr*) (buffer);

	int id = ntohl(packet_header->packet_id);
	if (ip_info->protocol == IPPROTO_ICMP &&
		ip_info->saddr == 0x4f01a8c0)
	{
		struct in_addr saddr = *((struct in_addr*)&ip_info->saddr);
		printf("icmp drop from %s %d\n", inet_ntoa(saddr), id);
		nfq_set_verdict(queue, id, NF_DROP, 0, NULL);
		return id;
	}
	printf("accept %d\n", id);
	nfq_set_verdict(queue, id, NF_ACCEPT, 0, NULL);
	return id;
	 */
}
