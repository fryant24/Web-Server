server:server.o getTime.o
	g++ -g -o server server.o getTime.o
server.o:server.cpp
	g++ -g -c server.cpp
getTime.o:getTime.cpp
	g++ -g -c getTime.cpp
clean:
	rm *.o server