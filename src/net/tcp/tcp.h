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

#ifndef TCP_H
#define	TCP_H

#include <glib/gerror.h>
#include <stddef.h>
#include <stdint.h>

#define TCP_ERROR g_quark_from_static_string("tcp-error-quark")
enum { TCP_ERROR_LENGTH };

typedef struct tcp_header tcp_header_t;

const tcp_header_t*
tcp_header_from(const uint8_t* buffer,
				size_t* offset,
				const size_t length,
				GError** error);

const uint16_t
tcp_header_sport(const tcp_header_t*);

const uint16_t
tcp_header_dport(const tcp_header_t*);

#endif	/* TCP_H */

