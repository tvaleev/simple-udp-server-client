CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g

all: udp_client udp_server

udp_server: udp_echo_server.cpp
	$(CXX) $(CXXFLAGS) -o server udp_echo_server.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

udp_client: udp_echo_client.cpp
	$(CXX) $(CXXFLAGS) -o client udp_echo_client.cpp udp_socket.cpp socket_exception.cpp socket.cpp communicating_socket.cpp $(LIBS)

clean:
	$(RM) udp_client udp_server