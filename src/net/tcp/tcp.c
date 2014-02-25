#include "tcp.h"

#include <netinet/tcp.h>
#include <asm/byteorder.h>

typedef struct tcphdr tcp_header;

const tcp_header_t *tcp_header_from(const uint8_t *buffer, size_t *offset,
                                    const size_t length, GError **error) {
  size_t effective_length = length - *offset;
  if (effective_length < sizeof(tcp_header)) {
    g_set_error(error, TCP_ERROR, TCP_ERROR_LENGTH, "Tcp length %zu < %zu",
                effective_length, sizeof(tcp_header));
    return NULL;
  }
  const tcp_header_t *header = (const tcp_header_t *)(buffer + *offset);
  (*offset) += sizeof(tcp_header);
  return header;
}

const uint16_t tcp_header_sport(const tcp_header_t *self) {
  return __be16_to_cpu(((const tcp_header *)self)->source);
}

const uint16_t tcp_header_dport(const tcp_header_t *self) {
  return __be16_to_cpu(((const tcp_header *)self)->dest);
}