#ifndef SOCKET_H_
#define SOCKET_H_

#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string>

#include "socket_exception.h"

// Function to fill in address structure an address and port
static void fillAddr(const std::string &address, unsigned short port, 
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

class Socket {
public:
  ~Socket();

  std::string getLocalAddress();
  unsigned short getLocalPort();

  int getSocketDescriptor() { return sock_desc_; }

  void setLocalPort(unsigned short localPort);
  void setLocalAddressAndPort(const std::string &localAddress, 
                              unsigned short localPort = 0);

  static unsigned short resolveService(const std::string &service,
                                       const std::string &protocol = "udp");

private:
  Socket(const Socket &sock);
  void operator=(const Socket &sock);

protected:
  Socket(int type, int protocol);
  Socket(int sockDesc);

  int sock_desc_;
};

#endif // SOCKET_H_