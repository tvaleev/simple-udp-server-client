#ifndef SOCKET_UTILS_H_
#define SOCKET_UTILS_H_

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string>

// Function to fill in address structure an address and port
void fillAddr(const std::string &address, unsigned short port, 
                     sockaddr_in &addr);

#endif // SOCKET_UTILS_H_