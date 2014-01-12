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

#ifndef ETH_H
#define	ETH_H

#include "../mac/mac.h"

#include <glib/gerror.h>
#include <stdint.h>

#define ETH_ERROR g_quark_from_static_string("eth-error-quark")
enum { ETH_ERROR_LENGTH, ETH_ERROR_TYPE };

typedef struct eth_header eth_header_t;

#pragma pack(push,1)
typedef enum
{
	eth_type_pup = 0x0200,
	eth_type_sprite = 0x0500,
	eth_type_ip = 0x0800,
	eth_type_arp = 0x0806,
	eth_type_revarp = 0x8035,
	eth_type_at = 0x809B,
	eth_type_aarp = 0x80F3,
	eth_type_vlan = 0x8100,
	eth_type_ipx = 0x8137,
	eth_type_ipv6 = 0x86dd,
	eth_type_loopback = 0x9000,
} eth_type_t;
#pragma pack(pop)

const eth_header_t*
eth_header_from(const uint8_t* buffer,
				size_t* offset,
				const size_t length,
				GError** error);

const macaddr_t*
eth_header_dhost(const eth_header_t*);

const macaddr_t*
eth_header_shost(const eth_header_t*);

const eth_type_t
eth_header_type(const eth_header_t*);

#endif	/* ETH_H */
