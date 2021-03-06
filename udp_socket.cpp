#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include <errno.h>
#include <cstring>

#include "udp_socket.h"
#include "socket_exception.h"
#include "socket_utils.h"

typedef void raw_type;

UDPSocket::UDPSocket() : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
}

UDPSocket::UDPSocket(unsigned short localPort) 
  : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
    setLocalPort(localPort);
}

UDPSocket::UDPSocket(const std::string &localAddress, unsigned short localPort) 
  : CommunicatingSocket(SOCK_DGRAM, IPPROTO_UDP) {
  setLocalAddressAndPort(localAddress, localPort);
}

void UDPSocket::disconnect() {
  sockaddr_in nullAddr;
  memset(&nullAddr, 0, sizeof(nullAddr));
  nullAddr.sin_family = AF_UNSPEC;

  // Try to disconnect
  if (::connect(getSocketDescriptor(), (sockaddr *) &nullAddr, sizeof(nullAddr)) < 0) {
    if (errno != EAFNOSUPPORT) {
      throw SocketException("Disconnect failed", true);
    }
  }
}

void UDPSocket::sendTo(const void *buffer, int bufferLen, 
    const std::string &foreignAddress, unsigned short foreignPort) {
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Write out the whole buffer as a single message.
  if (sendto(getSocketDescriptor(), (raw_type *) buffer, bufferLen, 0,
             (sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen) {
    throw SocketException("Send failed", true);
  }
}

int UDPSocket::recvFrom(void *buffer, int bufferLen, std::string &sourceAddress,
    unsigned short &sourcePort) {
  sockaddr_in clntAddr;
  socklen_t addrLen = sizeof(clntAddr);
  int rtn;
  if ((rtn = recvfrom(getSocketDescriptor(), (raw_type *) buffer, bufferLen, 0, 
                      (sockaddr *) &clntAddr, (socklen_t *) &addrLen)) < 0) {
    throw SocketException("Receive failed", true);
  }
  sourceAddress = inet_ntoa(clntAddr.sin_addr);
  sourcePort = ntohs(clntAddr.sin_port);

  return rtn;
}

bool UDPSocket::hasPendingDatagramms() const {
  ssize_t readBytes;
  char c;
  do {
    readBytes = ::recv(sock_desc_, &c, 1, MSG_PEEK);
  } while (readBytes == -1 && errno == EINTR);

  bool result = (readBytes != -1) || errno == EMSGSIZE;
  return result;
}

int UDPSocket::pendingDatagramSize() const {
  ssize_t recvResult = -1;
  char c;
  do {
    recvResult = ::recv(sock_desc_, &c, 1, MSG_PEEK | MSG_TRUNC);
  } while (recvResult == -1 && errno == EINTR);

  return recvResult;
}