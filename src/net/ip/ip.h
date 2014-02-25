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

#ifndef IP_H
#define IP_H

#include <glib.h>
#include <stddef.h>
#include <stdint.h>

#define IP_ERROR g_quark_from_static_string("ip-error-quark")

enum {
  IP_ERROR_LENGTH,
  IP_ERROR_PROTOCOL
};

#pragma pack(push, 1)
typedef enum {
  ip_protocol_hopopt = 0x00,
  ip_protocol_icmp = 0x01,
  ip_protocol_igmp = 0x02,
  ip_protocol_ggp = 0x03,
  ip_protocol_ipv4 = 0x04,
  ip_protocol_st = 0x05,
  ip_protocol_tcp = 0x06,
  ip_protocol_cbt = 0x07,
  ip_protocol_egp = 0x08,
  ip_protocol_igp = 0x09,
  ip_protocol_bbn_rcc_mon = 0x0A,
  ip_protocol_nvp_ii = 0x0B,
  ip_protocol_pup = 0x0C,
  ip_protocol_argus = 0x0D,
  ip_protocol_emcon = 0x0E,
  ip_protocol_xnet = 0x0F,
  ip_protocol_chaos = 0x10,
  ip_protocol_udp = 0x11,
  ip_protocol_mux = 0x12,
  ip_protocol_dcn_meas = 0x13,
  ip_protocol_hmp = 0x14,
  ip_protocol_prm = 0x15,
  ip_protocol_xns_idp = 0x16,
  ip_protocol_trunk_1 = 0x17,
  ip_protocol_trunk_2 = 0x18,
  ip_protocol_leaf_1 = 0x19,
  ip_protocol_leaf_2 = 0x1A,
  ip_protocol_rdp = 0x1B,
  ip_protocol_irtp = 0x1C,
  ip_protocol_iso_tp4 = 0x1D,
  ip_protocol_netblt = 0x1E,
  ip_protocol_mfe_nsp = 0x1F,
  ip_protocol_merit_inp = 0x20,
  ip_protocol_dccp = 0x21,
  ip_protocol_3pc = 0x22,
  ip_protocol_idpr = 0x23,
  ip_protocol_xtp = 0x24,
  ip_protocol_ddp = 0x25,
  ip_protocol_idpr_cmtp = 0x26,
  ip_protocol_tpplusplus = 0x27,
  ip_protocol_il = 0x28,
  ip_protocol_ipv6 = 0x29,
  ip_protocol_sdrp = 0x2A,
  ip_protocol_ipv6_route = 0x2B,
  ip_protocol_ipv6_frag = 0x2C,
  ip_protocol_idrp = 0x2D,
  ip_protocol_rsvp = 0x2E,
  ip_protocol_gre = 0x2F,
  ip_protocol_mhrp = 0x30,
  ip_protocol_bna = 0x31,
  ip_protocol_esp = 0x32,
  ip_protocol_ah = 0x33,
  ip_protocol_i_nlsp = 0x34,
  ip_protocol_swipe = 0x35,
  ip_protocol_narp = 0x36,
  ip_protocol_mobile = 0x37,
  ip_protocol_tlsp = 0x38,
  ip_protocol_skip = 0x39,
  ip_protocol_ipv6_icmp = 0x3A,
  ip_protocol_ipv6_nonxt = 0x3B,
  ip_protocol_ipv6_opts = 0x3C,
  ip_protocol_host_internal = 0x3D,
  ip_protocol_cftp = 0x3E,
  ip_protocol_local_network = 0x3F,
  ip_protocol_sat_expak = 0x40,
  ip_protocol_kryptolan = 0x41,
  ip_protocol_rvd = 0x42,
  ip_protocol_ippc = 0x43,
  ip_protocol_distributed_fs = 0x44,
  ip_protocol_sat_mon = 0x45,
  ip_protocol_visa = 0x46,
  ip_protocol_ipcv = 0x47,
  ip_protocol_cpnx = 0x48,
  ip_protocol_cphb = 0x49,
  ip_protocol_wsn = 0x4A,
  ip_protocol_pvp = 0x4B,
  ip_protocol_br_sat_mon = 0x4C,
  ip_protocol_sun_nd = 0x4D,
  ip_protocol_wb_mon = 0x4E,
  ip_protocol_wb_expak = 0x4F,
  ip_protocol_iso_ip = 0x50,
  ip_protocol_vmtp = 0x51,
  ip_protocol_secure_vmtp = 0x52,
  ip_protocol_vines = 0x53,
  ip_protocol_ttp = 0x54,
  ip_protocol_iptm = 0x54,
  ip_protocol_nsfnet_igp = 0x55,
  ip_protocol_dgp = 0x56,
  ip_protocol_tcf = 0x57,
  ip_protocol_eigrp = 0x58,
  ip_protocol_ospf = 0x59,
  ip_protocol_sprite_rpc = 0x5A,
  ip_protocol_larp = 0x5B,
  ip_protocol_mtp = 0x5C,
  ip_protocol_ax25 = 0x5D,
  ip_protocol_ipip = 0x5E,
  ip_protocol_micp = 0x5F,
  ip_protocol_scc_sp = 0x60,
  ip_protocol_etherip = 0x61,
  ip_protocol_encap = 0x62,
  ip_protocol_private_encryption = 0x63,
  ip_protocol_gmtp = 0x64,
  ip_protocol_ifmp = 0x65,
  ip_protocol_pnni = 0x66,
  ip_protocol_pim = 0x67,
  ip_protocol_aris = 0x68,
  ip_protocol_scps = 0x69,
  ip_protocol_qnx = 0x6A,
  ip_protocol_adivn = 0x6B,
  ip_protocol_ipcomp = 0x6C,
  ip_protocol_snp = 0x6D,
  ip_protocol_compaq_peer = 0x6E,
  ip_protocol_ipx_in_ip = 0x6F,
  ip_protocol_vrrp = 0x70,
  ip_protocol_pgm = 0x71,
  ip_protocol_0hop = 0x72,
  ip_protocol_l2tp = 0x73,
  ip_protocol_ddx = 0x74,
  ip_protocol_iatp = 0x75,
  ip_protocol_stp = 0x76,
  ip_protocol_srp = 0x77,
  ip_protocol_uti = 0x78,
  ip_protocol_smp = 0x79,
  ip_protocol_sm = 0x7A,
  ip_protocol_ptp = 0x7B,
  ip_protocol_is_is_over_ipv4 = 0x7C,
  ip_protocol_fire = 0x7D,
  ip_protocol_crtp = 0x7E,
  ip_protocol_crudp = 0x7F,
  ip_protocol_sscopmce = 0x80,
  ip_protocol_iplt = 0x81,
  ip_protocol_sps = 0x82,
  ip_protocol_pipe = 0x83,
  ip_protocol_sctp = 0x84,
  ip_protocol_fc = 0x85,
  ip_protocol_rsvp_e2e_ignore = 0x86,
  ip_protocol_mobility_header = 0x87,
  ip_protocol_udplite = 0x88,
  ip_protocol_mpls_in_ip = 0x89,
  ip_protocol_manet = 0x8A,
  ip_protocol_hip = 0x8B,
  ip_protocol_shim6 = 0x8C,
  ip_protocol_wesp = 0x8D,
  ip_protocol_rohc = 0x8E
} ip_protocol_t;
#pragma pack(pop)

typedef struct ip_header ip_header_t;

const char *ip_protocol_to_string(const ip_protocol_t);

const ip_header_t *ip_header_from(const uint8_t *buffer, size_t *offset,
                                  const size_t length, GError **error);

const uint32_t ip_header_saddr(const ip_header_t *);

const uint32_t ip_header_daddr(const ip_header_t *);

const ip_protocol_t ip_header_protocol(const ip_header_t *);

#endif /* IP_H */
