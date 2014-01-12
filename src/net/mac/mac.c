#include "mac.h"

#include <glib/gmain.h>
#include <stdio.h>

const size_t MACADDR_LENGTH = 6;

char*
macaddr_to_string(const macaddr_t self)
{
	char* macaddr = g_new(char, 19);
	snprintf(macaddr, 19, "%02x:%02x:%02x:%02x:%02x:%02x", self[0], self[1], self[2], self[3], self[4], self[5]);
	return macaddr;
}
