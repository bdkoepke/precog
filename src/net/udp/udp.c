#include "udp.h"

#include <netinet/udp.h>
#include <asm/byteorder.h>

typedef struct udphdr udp_header;

const udp_header_t *udp_header_from(const uint8_t *buffer, size_t *offset,
                                    const size_t length, GError **error) {
  size_t effective_length = length - *offset;
  if (effective_length < sizeof(udp_header)) {
    g_set_error(error, UDP_ERROR, UDP_ERROR_LENGTH, "Udp length %zu < %zu",
                effective_length, sizeof(udp_header));
    return NULL;
  }
  const udp_header_t *header = (const udp_header_t *)(buffer + *offset);
  (*offset) += sizeof(udp_header);
  return header;
}

const uint16_t udp_header_sport(const udp_header_t *header) {
  return __be16_to_cpu(((const udp_header *)header)->source);
}

const uint16_t udp_header_dport(const udp_header_t *header) {
  return __be16_to_cpu(((const udp_header *)header)->dest);
}
