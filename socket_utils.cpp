#include <cstring>

#include "socket_utils.h"
#include "socket_exception.h"

void fillAddr(const std::string &address, unsigned short port, 
                     sockaddr_in &addr) {
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;

  hostent *host;
  if ((host = gethostbyname(address.c_str())) == NULL) {
    throw SocketException("Failed to resolve name");
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);
}