#include "eth.h"

#include <netinet/ether.h>
#include <stdbool.h>

typedef struct ether_header eth_header;

static bool
eth_header_is_type_valid(uint16_t ether_type)
{
	switch (ether_type)
	{
	case eth_type_pup:
	case eth_type_sprite:
	case eth_type_ip:
	case eth_type_arp:
	case eth_type_revarp:
	case eth_type_at:
	case eth_type_aarp:
	case eth_type_vlan:
	case eth_type_ipx:
	case eth_type_ipv6:
	case eth_type_loopback:
		return true;
	}
	return false;
}

const eth_header_t*
eth_header_from(const uint8_t* buffer,
									size_t* offset,
									const size_t length,
									GError** error)
{
	const size_t effective_length = length - *offset;
	if (effective_length < ETHER_MIN_LEN)
	{
		g_set_error(error, ETH_ERROR, ETH_ERROR_LENGTH, "Eth length %zu < %ul", effective_length, ETHER_MIN_LEN);
		return NULL;
	}
	const eth_header* header = (const eth_header*)(buffer + *offset);
	if (! eth_header_is_type_valid(header->ether_type))
	{
		g_set_error(error, ETH_ERROR, ETH_ERROR_TYPE, "Eth type %d invalid", header->ether_type);
		return NULL;
	}

	(*offset) += sizeof(eth_header);
	return (const eth_header_t*)header;
}

const macaddr_t*
eth_header_dhost(const eth_header_t* self)
{
	return (const macaddr_t*)((const eth_header*)self)->ether_dhost;
}

const macaddr_t*
eth_header_shost(const eth_header_t* self)
{
	return (const macaddr_t*)((const eth_header*)self)->ether_shost;
}

const eth_type_t
eth_header_type(const eth_header_t* self)
{
	return (const eth_type_t)((const eth_header*)self)->ether_type;
}