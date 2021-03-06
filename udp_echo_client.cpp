#include <iostream>
#include <cstdlib>
#include <cstring>

#include "udp_socket.h"
#include "socket_exception.h"

using namespace std;

const int ECHOMAX = 255;

int main(int argc, char *argv[]) {
  if ((argc != 5)) {
    cerr << "Usage: " << argv[0] 
         << " <Client port> <Server> <Echo String> <Server Port>\n";
    exit(1);
  }

  string userInputlocalPort = argv[1]; // local client port
  string servAddress = argv[2]; // server address
  char* echoString = argv[3]; // string to echo
  int echoStringLen = strlen(echoString);
  if (echoStringLen > ECHOMAX) {
    cerr << "Echo string too long" << endl;
    exit(1);
  }
  unsigned short echoServPort = Socket::resolveService(argv[4], "udp");

  try {
    UDPSocket sock(std::atoi(userInputlocalPort.c_str()));
  
    // 1. send the string to the server
    sock.sendTo(echoString, echoStringLen, servAddress, echoServPort);
  
    // 2. receive a response from server
    char echoBuffer[ECHOMAX + 1];
    int responseStringLen;
    if ((responseStringLen = sock.recv(echoBuffer, ECHOMAX)) != echoStringLen) {
      cerr << "Unable to receive" << endl;
      exit(1);
    }
  
    echoBuffer[responseStringLen] = '\0';
    cout << "Received: " << echoBuffer << endl;

  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
  
  return 0;
}