#include <iostream>
#include <cstdlib>

#include "tcp_server_socket.h"
#include "socket_exception.h"

const unsigned int RCVBUFSIZE = 32;

void HandleTCPClient(TCPSocket *sock);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <Server Port>" << std::endl;
    exit(1);
  }

  unsigned short echoServPort = atoi(argv[1]);

  try {
    TCPServerSocket servSock(echoServPort);
  
    for (;;) { 
      HandleTCPClient(servSock.accept());
    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  return 0;
}

void HandleTCPClient(TCPSocket *sock) {
  std::cout << "Handling client ";
  try {
    std::cout << sock->getForeignAddress() << ":";
  } catch (SocketException &e) {
    std::cerr << "Unable to get foreign address" << std::endl;
  }
  try {
    std::cout << sock->getForeignPort();
  } catch (SocketException &e) {
    std::cerr << "Unable to get foreign port" << std::endl;
  }
  std::cout << std::endl;

  char echoBuffer[RCVBUFSIZE];
  int recvMsgSize;
  while ((recvMsgSize = sock->recv(echoBuffer, RCVBUFSIZE)) > 0) {
    sock->send(echoBuffer, recvMsgSize);
  }
  delete sock;
}
