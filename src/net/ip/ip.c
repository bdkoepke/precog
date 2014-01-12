#include "ip.h"

#include <netinet/ip.h>
#include <asm/byteorder.h>

typedef struct iphdr ip_header;

const ip_header_t*
ip_header_from(const uint8_t* buffer,
		size_t* offset,
		const size_t length,
		GError** error)
{
	size_t effective_length = length - *offset;
	if (effective_length < sizeof(ip_header))
	{
		g_set_error(error, IP_ERROR, IP_ERROR_LENGTH, "Ip length %zu < %zu", effective_length, sizeof(ip_header));
		return NULL;
	}
	const ip_header* header =  (const ip_header*)(buffer + *offset);
	if (header->protocol > 0x8f) {
		g_set_error(error, IP_ERROR, IP_ERROR_PROTOCOL, "Ip protocol %d > %d", header->protocol, 0x8f);
		return NULL;
	}
	(*offset) += sizeof(ip_header);
	return (const ip_header_t*)header;
}

const uint32_t
ip_header_saddr(const ip_header_t* self)
{
	return __be32_to_cpu(((const ip_header*)self)->saddr);
}

const uint32_t
ip_header_daddr(const ip_header_t* self)
{
	return __be32_to_cpu(((const ip_header*)self)->daddr);
}

const ip_protocol_t
ip_header_protocol(const ip_header_t* self)
{
	return ((const ip_header*)self)->protocol;
}