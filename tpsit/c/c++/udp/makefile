default: serverUDP
clean:
	rm serverUDP udp.o
udp.o: udp.cpp
	g++ -c udp.cpp -o udp.o
serverUDP: udp.o serverUDP.cpp
	g++ serverUDP.cpp udp.o -o serverUDP
