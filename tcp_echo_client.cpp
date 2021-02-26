#include <iostream>
#include <cstdlib>
#include <cstring>

#include "tcp_socket.h"

const int RCVBUFSIZE = 32;

int main(int argc, char *argv[]) {
  if ((argc < 3) || (argc > 4)) {     // Test for correct number of arguments
    std::cerr << "Usage: " << argv[0] 
         << " <Server> <Echo String> [<Server Port>]" << std::endl;
    exit(1);
  }

  std::string servAddress = argv[1]; // server address
  char *echoString = argv[2];   // string to echo
  int echoStringLen = strlen(echoString);
  unsigned short echoServPort = (argc == 4) ? atoi(argv[3]) : 7;

  try {
    TCPSocket sock(servAddress, echoServPort);
  
    sock.send(echoString, echoStringLen);
  
    char echoBuffer[RCVBUFSIZE + 1];    // buffer for echo string + \0
    int bytesReceived = 0;              // bytes read on each recv()
    int totalBytesReceived = 0;         // total bytes read

    std::cout << "Received: ";
    while (totalBytesReceived < echoStringLen) {
      if ((bytesReceived = (sock.recv(echoBuffer, RCVBUFSIZE))) <= 0) {
        std::cerr << "Unable to read";
        exit(1);
      }
      totalBytesReceived += bytesReceived;
      echoBuffer[bytesReceived] = '\0';
      std::cout << echoBuffer;
    }
    std::cout << std::endl;

  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return 0;
}

