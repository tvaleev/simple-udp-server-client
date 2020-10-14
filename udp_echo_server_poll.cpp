#include <iostream>
#include <cstdlib>
#include <poll.h>

#include "udp_socket.h"
#include "socket_exception.h"

const int ECHOMAX = 255;
const int MAX_CONN = 2;
const int TIMEOUT = 1024 * 1024;
const int POLL_ERR = -1;
const int POLL_EXPIRE = 0;

int main(int argc, char *argv[]) {

  UDPSocket socks[MAX_CONN];
  struct pollfd pfds[MAX_CONN];
  int j = 0;

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <Server Port>" << std::endl;
    exit(1);
  }

  unsigned short echoServPort = atoi(argv[1]); // local port

  try {
    for (auto i = 0; i < MAX_CONN; i++ ) {
      socks[i].setLocalPort(echoServPort + i);

      pfds[i].fd = socks[i].getSocketDescriptor();
		  pfds[i].events = POLLIN ;
    }
  
    char echoBuffer[ECHOMAX];
    int recvMsgSize;
    std::string sourceAddress;
    unsigned short sourcePort;
    for (;;) {
      j = poll(pfds, (unsigned int)MAX_CONN, TIMEOUT);

      switch (j)
      {
      case POLL_EXPIRE:
        std::cout << "Timeout has expired!\n";
        break;
      case POLL_ERR:
        std::cerr << "Error on poll\n";

      default:
        for (auto i =0; i < MAX_CONN; i++ ) {
          if (pfds[i].revents & POLLIN ) {
            std::cout << "We have a connection\n";
            recvMsgSize = socks[i].recvFrom(echoBuffer, ECHOMAX, sourceAddress,
                                            sourcePort);
            std::cout << "Received packet from " << sourceAddress << ":"
                      << sourcePort << std::endl;
            socks[i].sendTo(echoBuffer, recvMsgSize, sourceAddress, sourcePort);
          }
        }
      }
    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return 0;
}