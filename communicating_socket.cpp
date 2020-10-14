#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "communicating_socket.h"
#include "socket_utils.h"

typedef void raw_type;

CommunicatingSocket::CommunicatingSocket(int type, int protocol)  
  : Socket(type, protocol) {
}

CommunicatingSocket::CommunicatingSocket(int newConnSD) : Socket(newConnSD) {
}

void CommunicatingSocket::connect(const std::string &foreignAddress,
                                  unsigned short foreignPort) {
  // Get the address of the requested host
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Try to connect to the given port
  if (::connect(sock_desc_, (sockaddr *) &destAddr, sizeof(destAddr)) < 0) {
    throw SocketException("Connect failed", true);
  }
}

void CommunicatingSocket::send(const void *buffer, int bufferLen) {
  if (::send(sock_desc_, (raw_type *) buffer, bufferLen, 0) < 0) {
    throw SocketException("Send failed", true);
  }
}

int CommunicatingSocket::recv(void *buffer, int bufferLen) {
  int rtn;
  if ((rtn = ::recv(sock_desc_, (raw_type *) buffer, bufferLen, 0)) < 0) {
    throw SocketException("Received failed", true);
  }

  return rtn;
}

std::string CommunicatingSocket::getForeignAddress() {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sock_desc_, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of foreign address failed", true);
  }
  return inet_ntoa(addr.sin_addr);
}

unsigned short CommunicatingSocket::getForeignPort() {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sock_desc_, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of foreign port failed", true);
  }
  return ntohs(addr.sin_port);
}