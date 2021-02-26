#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <string>
#include <exception>

#include "socket.h"
#include "communicating_socket.h"

class UDPSocket : public CommunicatingSocket {
public:
  UDPSocket();
  explicit UDPSocket(unsigned short localPort);
  UDPSocket(const std::string &localAddress, unsigned short localPort);

  void disconnect();
  void sendTo(const void *buffer, int bufferLen, const std::string &foreignAddress,
              unsigned short foreignPort);
  int recvFrom(void *buffer, int bufferLen, std::string &sourceAddress, 
                unsigned short &sourcePort);
};

#endif // UDP_SOCKET_H