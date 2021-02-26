#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

#include "socket_exception.h"

class Socket {
public:
  virtual ~Socket();

  std::string getLocalAddress();
  unsigned short getLocalPort();

  int getSocketDescriptor() { return sock_desc_; }

  void setLocalPort(unsigned short localPort);
  void setLocalAddressAndPort(const std::string &localAddress, 
                              unsigned short localPort = 0);

  static unsigned short resolveService(const std::string &service,
                                       const std::string &protocol = "udp");

private:
  Socket(const Socket &sock);
  void operator=(const Socket &sock);

protected:
  Socket(int type, int protocol);
  explicit Socket(int sockDesc);

  int sock_desc_;
};

#endif // SOCKET_H_
