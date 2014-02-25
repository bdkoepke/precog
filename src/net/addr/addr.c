#include "addr.h"

#include <arpa/inet.h>

char *addr_to_string(addr_t addr) {
  return inet_ntoa(*((struct in_addr *)&addr));
}
