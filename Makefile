CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g -std=c++11

all: udp_client udp_server udp_server_poll

udp_server: udp_echo_server.cpp
	$(CXX) $(CXXFLAGS) -o server udp_echo_server.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

udp_server_poll: udp_echo_server_poll.cpp
	$(CXX) $(CXXFLAGS) -o server_poll udp_echo_server_poll.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

udp_client: udp_echo_client.cpp
	$(CXX) $(CXXFLAGS) -o client udp_echo_client.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

clean:
	$(RM) udp_client udp_server
