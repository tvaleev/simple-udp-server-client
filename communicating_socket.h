#ifndef COMMUNICATION_SOCKET_H_
#define COMMUNICATION_SOCKET_H_

#include <string>

#include "socket.h"

class CommunicatingSocket : public Socket {
public:
  void connect(const std::string &foreignAddress, unsigned short foreignPort);
  void send(const void *buffer, int bufferLen);
  int recv(void *buffer, int bufferLen);

  std::string getForeignAddress();

  unsigned short getForeignPort();

protected:
  CommunicatingSocket(int type, int protocol);
  CommunicatingSocket(int newConnSD);
};

#endif // COMMUNICATION_SOCKET_H_