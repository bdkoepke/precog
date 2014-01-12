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

#include <stdio.h>
#include <stdlib.h>
#include <glib/gerror.h>

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
			nfq_close(handle);
			}
		nfq_destroy_queue(queue);
		}
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
