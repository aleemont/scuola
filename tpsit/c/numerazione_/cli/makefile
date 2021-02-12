default: client
clean:
	rm client udp.o
udp.o: udp.c
	gcc -c udp.c -o udp.o
client: udp.o client.c
	gcc client.c udp.o -o client
