#include <cstring>
#include <string>
#include <exception>
#include <errno.h>

#include "socket_exception.h"

SocketException::SocketException(const std::string &message, bool inclSysMsg)
  throw() : user_message_(message) {
  if (inclSysMsg) {
    user_message_.append(": ");
    user_message_.append(std::strerror(errno));
  }
}

SocketException::~SocketException() throw() {
}

const char *SocketException::what() const throw() {
  return user_message_.c_str();
}