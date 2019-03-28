server:main.o server.o getTime.o myepoll.o
	g++ -g -o server main.o server.o getTime.o myepoll.o
main.o:main.cpp
	g++ -g -c main.cpp
server.o:server.cpp
	g++ -g -c server.cpp
getTime.o:getTime.cpp
	g++ -g -c getTime.cpp
myepoll.o:myepoll.cpp
	g++ -g -c myepoll.cpp
clean:
	rm *.o server