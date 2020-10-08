#include <iostream>
#include <cstdlib>

#include "udp_socket.h"
#include "socket_exception.h"

const int ECHOMAX = 255;

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <Server Port>" << std::endl;
    exit(1);
  }

  unsigned short echoServPort = atoi(argv[1]); // local port

  try {
    UDPSocket sock(echoServPort);                
  
    char echoBuffer[ECHOMAX];
    int recvMsgSize;
    std::string sourceAddress;
    unsigned short sourcePort;
    for (;;) {
      // Block until receive message from a client
      recvMsgSize = sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress, 
                                  sourcePort);
  
      std::cout << "Received packet from " << sourceAddress << ":" 
           << sourcePort << std::endl;
  
      sock.sendTo(echoBuffer, recvMsgSize, sourceAddress, sourcePort);
    }
  } catch (SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return 0;
}