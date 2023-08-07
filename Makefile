clean:
	rm -fr client libnetstack server netstack.o
libnetstack: netstack.hpp netstack.cpp
	g++ netstack.cpp -o netstack.o -c -fPIC
	ar rcs libnetstack netstack.o
	rm netstack.o

server: server.cpp libnetstack
	g++ server.cpp -o server -l:libnetstack -L ./
	
client: client.cpp libnetstack
	g++ client.cpp -o client -l:libnetstack -L ./

all: netstack.hpp netstack.cpp server.cpp client.cpp
	rm -fr client libnetstack server netstack.o
	g++ netstack.cpp -o netstack.o -c -fPIC
	ar rcs libnetstack netstack.o
	rm netstack.o
	g++ client.cpp -o client -l:libnetstack -L ./
	g++ server.cpp -o server -l:libnetstack -L ./

