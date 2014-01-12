#include "dns.h"

typedef struct dns_header dns_header_t;

const dns_header_t*
dns_header_from(const uint8_t* buffer,
				size_t* offset,
				const size_t length,
				GError** error);