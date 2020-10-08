#ifndef SOCKET_EXCEPTION_H_
#define SOCKET_EXCEPTION_H_

#include <exception>
#include <string>

class SocketException : public std::exception {
public:
  SocketException(const std::string &message, bool inclSysMsg = false) throw();
  ~SocketException() throw();

  const char *what() const throw();
private:
  std::string user_message_;
};

#endif // SOCKET_EXCEPTION_H_