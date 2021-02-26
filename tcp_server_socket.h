#ifndef TCP_SERVER_SOCKET_H
#define TCP_SERVER_SOCKET_H

#include <string>

#include "socket.h"
#include "tcp_socket.h"

class TCPServerSocket : public Socket {
public:
  TCPServerSocket(unsigned short localPort, int queueLen = 30);

  TCPServerSocket(const std::string &localAddress, unsigned short localPort,
                  int queueLen = 30);

  TCPSocket *accept();

private:
  void setListen(int queueLen);
};

#endif // TCP_SERVER_SOCKET_H