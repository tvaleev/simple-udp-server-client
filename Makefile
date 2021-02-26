CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g -std=c++11

all: udp_client udp_server udp_server_poll tcp_echo_client tcp_echo_server

udp_server: udp_echo_server.cpp
	$(CXX) $(CXXFLAGS) -o server udp_echo_server.cpp socket_utils.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

udp_server_poll: udp_echo_server_poll.cpp
	$(CXX) $(CXXFLAGS) -o server_poll udp_echo_server_poll.cpp socket_utils.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

udp_client: udp_echo_client.cpp
	$(CXX) $(CXXFLAGS) -o client udp_echo_client.cpp socket_utils.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

tcp_echo_client: tcp_echo_client.cpp
	$(CXX) $(CXXFLAGS) -o tcp_client tcp_echo_client.cpp socket_utils.cpp tcp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

tcp_echo_server: tcp_echo_server.cpp
	$(CXX) $(CXXFLAGS) -o tcp_server tcp_echo_server.cpp tcp_server_socket.cpp socket_utils.cpp tcp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

clean:
	$(RM) udp_client udp_server tcp_echo_client tcp_echo_server
