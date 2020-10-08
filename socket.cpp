#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netinet/in.h>
#include <string>

#include "socket.h"
#include "socket_exception.h"

Socket::Socket(int type, int protocol) {
  if ((sock_desc_ = socket(PF_INET, type, protocol)) < 0) {
    throw SocketException("Socket creation failed", true);
  }
}

Socket::Socket(int sock_desc_) {
  this->sock_desc_ = sock_desc_;
}

Socket::~Socket() {
  ::close(sock_desc_);
  sock_desc_ = -1;
}

std::string Socket::getLocalAddress() {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sock_desc_, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of local address failed", true);
  }
  return inet_ntoa(addr.sin_addr);
}

unsigned short Socket::getLocalPort() {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sock_desc_, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of local port failed", true);
  }
  return ntohs(addr.sin_port);
}

void Socket::setLocalPort(unsigned short localPort) {
  sockaddr_in localAddr;
  memset(&localAddr, 0, sizeof(localAddr));
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(localPort);

  if (bind(sock_desc_, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
    throw SocketException("Set of local port failed", true);
  }
}

void Socket::setLocalAddressAndPort(const std::string &localAddress,
    unsigned short localPort) {
  sockaddr_in localAddr;
  fillAddr(localAddress, localPort, localAddr);

  if (bind(sock_desc_, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
    throw SocketException("Set of local address and port failed", true);
  }
}

unsigned short Socket::resolveService(const std::string &service,
                                      const std::string &protocol) {
  struct servent *serv;

  if ((serv = getservbyname(service.c_str(), protocol.c_str())) == NULL)
    return std::atoi(service.c_str());
  else 
    return ntohs(serv->s_port);
}