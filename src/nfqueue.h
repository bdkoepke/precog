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

#ifndef NFQUEUE_H
#define NFQUEUE_H

#include <stdint.h>
#include <glib.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

#define NETFILTER_ERROR g_quark_from_static_string("NETFILTER_ERROR")
enum {
  NETFILTER_ERROR_INIT
};

/**
 * Netfilter queue callback.
 *
 * @param queue handle returned by nfq_create_queue.
 * @param message object that contains the packet.
 * @param nfa netlink packet data handle.
 * @param data the value passed to the data parameter
 *             of nfq_create_queue.
 * @return a value of < 0 stops processing.
 */
typedef int (*queue_callback_t)(struct nfq_q_handle *queue,
                                struct nfgenmsg *message, struct nfq_data *nfa,
                                void *user_data);

/**
 * Creates a new nfq queue handle that passes the entire packet.
 * 
 * @param handle the netfilter handle to create the queue from.
 * @param callback the callback function for the queue.
 * @param error the error handler for this handle.
 * @return a netfilter queue handle.
 */
struct nfq_q_handle *nfq_q_handle_new(struct nfq_handle *handle,
                                      queue_callback_t callback,
                                      GError **error);

/**
 * Creates a new nfq handle.
 *
 * @param error the error message.
 * @return the netfilter handle.
 */
struct nfq_handle *nfq_handle_new(GError **error);

/**
 * Creates a new nfqueue file descriptor.
 *
 * @param handle the nfq handle.
 * @param error an error pointer in case of failure.
 * @return the file descriptor or < 0 if error.
 */
size_t nfqueue_fd_new(struct nfq_handle *handle, GError **error);

#endif /* NFQUEUE_H */
