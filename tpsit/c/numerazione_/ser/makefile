default: server
clean:
	rm server udp.o
udp.o: udp.c
	gcc -c udp.c -o udp.o
server: udp.o server.c
	gcc server.c udp.o -o server
