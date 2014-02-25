#include "ip.h"

#include <netinet/ip.h>
#include <asm/byteorder.h>

typedef struct iphdr ip_header;

const ip_header_t *ip_header_from(const uint8_t *buffer, size_t *offset,
                                  const size_t length, GError **error) {
  size_t effective_length = length - *offset;
  if (effective_length < sizeof(ip_header)) {
    g_set_error(error, IP_ERROR, IP_ERROR_LENGTH, "Ip length %zu < %zu",
                effective_length, sizeof(ip_header));
    return NULL;
  }
  const ip_header *header = (const ip_header *)(buffer + *offset);
  if (header->protocol > 0x8f) {
    g_set_error(error, IP_ERROR, IP_ERROR_PROTOCOL, "Ip protocol %d > %d",
                header->protocol, 0x8f);
    return NULL;
  }
  (*offset) += sizeof(ip_header);
  return (const ip_header_t *)header;
}

const uint32_t ip_header_saddr(const ip_header_t *self) {
  return __be32_to_cpu(((const ip_header *)self)->saddr);
}

const uint32_t ip_header_daddr(const ip_header_t *self) {
  return __be32_to_cpu(((const ip_header *)self)->daddr);
}

const ip_protocol_t ip_header_protocol(const ip_header_t *self) {
  return ((const ip_header *)self)->protocol;
}

const char *ip_protocol_to_string(const ip_protocol_t protocol) {
  static const char *ip_protocol_map[] = {
    "hopopt", "icmp", "igmp", "ggp", "ipv4", "st", "tcp", "cbt", "egp", "igp",
    "bbn_rcc_mon", "nvp_ii", "pup", "argus", "emcon", "xnet", "chaos", "udp",
    "mux", "dcn_meas", "hmp", "prm", "xns_idp", "trunk_1", "trunk_2", "leaf_1",
    "leaf_2", "rdp", "irtp", "iso_tp4", "netblt", "mfe_nsp", "merit_inp",
    "dccp", "3pc", "idpr", "xtp", "ddp", "idpr_cmtp", "tpplusplus", "il",
    "ipv6", "sdrp", "ipv6_route", "ipv6_frag", "idrp", "rsvp", "gre", "mhrp",
    "bna", "esp", "ah", "i_nlsp", "swipe", "narp", "mobile", "tlsp", "skip",
    "ipv6_icmp", "ipv6_nonxt", "ipv6_opts", "host_internal", "cftp",
    "local_network", "sat_expak", "kryptolan", "rvd", "ippc", "distributed_fs",
    "sat_mon", "visa", "ipcv", "cpnx", "cphb", "wsn", "pvp", "br_sat_mon",
    "sun_nd", "wb_mon", "wb_expak", "iso_ip", "vmtp", "secure_vmtp", "vines",
    "ttp", "iptm", "nsfnet_igp", "dgp", "tcf", "eigrp", "ospf", "sprite_rpc",
    "larp", "mtp", "ax25", "ipip", "micp", "scc_sp", "etherip", "encap",
    "private_encryption", "gmtp", "ifmp", "pnni", "pim", "aris", "scps", "qnx",
    "adivn", "ipcomp", "snp", "compaq_peer", "ipx_in_ip", "vrrp", "pgm", "0hop",
    "l2tp", "ddx", "iatp", "stp", "srp", "uti", "smp", "sm", "ptp",
    "is_is_over_ipv4", "fire", "crtp", "crudp", "sscopmce", "iplt", "sps",
    "pipe", "sctp", "fc", "rsvp_e2e_ignore", "mobility_header", "udplite",
    "mpls_in_ip", "manet", "hip", "shim6", "wesp", "rohc"
  };
  return protocol < sizeof(ip_protocol_map) ? ip_protocol_map[protocol]
                                            : "unknown";
}