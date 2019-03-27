server:main.o server.o getTime.o
	g++ -g -o server main.o server.o getTime.o
main.o:main.cpp
	g++ -g -c main.cpp
server.o:server.cpp
	g++ -g -c server.cpp
getTime.o:getTime.cpp
	g++ -g -c getTime.cpp
clean:
	rm *.o server