#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include "socket.h"
#include "tcp_server_socket.h"

TCPServerSocket::TCPServerSocket(unsigned short localPort, int queueLen) 
 : Socket(SOCK_STREAM, IPPROTO_TCP) {
  setLocalPort(localPort);
  setListen(queueLen);
}

TCPServerSocket::TCPServerSocket(const std::string &localAddress, 
                                 unsigned short localPort, int queueLen) 
  : Socket(SOCK_STREAM, IPPROTO_TCP) {
  setLocalAddressAndPort(localAddress, localPort);
  setListen(queueLen);
}

TCPSocket *TCPServerSocket::accept() {
  int newConnSD;
  if ((newConnSD = ::accept(getSocketDescriptor(), NULL, 0)) < 0) {
    throw SocketException("Accept failed (accept())", true);
  }

  return new TCPSocket(newConnSD);
}

void TCPServerSocket::setListen(int queueLen) {
  if (listen(getSocketDescriptor(), queueLen) < 0) {
    throw SocketException("Set listening socket failed (listen())", true);
  }
}