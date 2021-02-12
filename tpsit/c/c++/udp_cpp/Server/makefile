default: server
clean:
	rm server UDP.o
UDP.o: UDP.cpp
	g++ -c UDP.cpp -o UDP.o
server: UDP.o server.cpp
	g++ server.cpp UDP.o -o server
