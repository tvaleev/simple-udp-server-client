#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <string>
#include <exception>

#include "socket.h"
#include "communicating_socket.h"

class TCPSocket : public CommunicatingSocket {
public:
  TCPSocket();
  TCPSocket(const std::string &foreignAddress, unsigned short foreignPort);
private:
  friend class TCPServerSocket;
  TCPSocket(int newConnSD);
};

#endif // TCP_SOCKET_H