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

typedef enum {
  NF_VERDICT_DROP = NF_DROP,
  NF_VERDICT_ACCEPT = NF_ACCEPT,
  NF_VERDICT_STOLEN = NF_STOLEN,
  NF_VERDICT_QUEUE = NF_QUEUE,
  NF_VERDICT_REPEAT = NF_REPEAT,
  NF_VERDICT_STOP = NF_STOP,
} nf_verdict_t;

typedef nf_verdict_t (*ip_protocol_verdict_f)(const uint8_t *buffer,
                                              size_t *offset,
                                              const size_t length,
                                              GError **error);

static bool dport_is_accept(uint32_t dport) {
  switch (dport) {
  case 53:
  case 80:
  case 443:
  case 8080:
  case 8081:
  case 8082:
  case 8083:
  case 8084:
    return true;
  }
  return false;
}

nf_verdict_t tcp_verdict(const uint8_t *buffer, size_t *offset,
                         const size_t length, GError **error) {
  const tcp_header_t *tcp_header =
      tcp_header_from(buffer, offset, length, error);
  //uint16_t sport = tcp_header_sport(tcp_header);
  uint16_t dport = tcp_header_dport(tcp_header);
  return dport_is_accept(dport) ? NF_VERDICT_ACCEPT : NF_VERDICT_DROP;
}

nf_verdict_t udp_verdict(const uint8_t *buffer, size_t *offset,
                         const size_t length, GError **error) {
  /*
 	const udp_header_t* udp_header = udp_header_from(buffer, offset, length,
 error);
 	uint16_t sport = udp_header_sport(udp_header);
 	uint16_t dport = udp_header_dport(udp_header);
 	 */
  return NF_VERDICT_ACCEPT;
}

nf_verdict_t icmp_verdict(const uint8_t *buffer, size_t *offset,
                          const size_t length, GError **error) {
  return NF_VERDICT_ACCEPT;
}

nf_verdict_t default_verdict(const uint8_t *buffer, size_t *offset,
                             const size_t length, GError **error) {
  return NF_VERDICT_ACCEPT;
}

const ip_protocol_verdict_f
ip_protocol_get_verdict_func(const ip_protocol_t protocol) {
  switch (protocol) {
  case ip_protocol_tcp:
    return tcp_verdict;
  case ip_protocol_udp:
    return udp_verdict;
  case ip_protocol_icmp:
    return icmp_verdict;
  default:
    return default_verdict;
  }
}

int queue_callback(struct nfq_q_handle *queue, struct nfgenmsg *genmessage,
                   struct nfq_data *nfa, void *user_data) {
  struct nfqnl_msg_packet_hdr *packet_header = nfq_get_msg_packet_hdr(nfa);
  if (packet_header == NULL)
    return -1;

  uint8_t *buffer;
  const size_t length = nfq_get_payload(nfa, &buffer);
  size_t offset = 0;
  int packet_number = ntohl(packet_header->packet_id);

  GError *error = NULL;
  const ip_header_t *ip_header =
      ip_header_from(buffer, &offset, length, &error);
  const ip_protocol_t ip_protocol = ip_header_protocol(ip_header);

  const char *protocol = ip_protocol_to_string(ip_protocol);
  nf_verdict_t verdict = ip_protocol_get_verdict_func(ip_protocol)(
      buffer, &offset, length, &error);
  printf("pkt: %d, proto: %s\n", packet_number, protocol);
  nfq_set_verdict(queue, packet_number, verdict, 0, NULL);
  return packet_number;
}
