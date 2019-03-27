#include "server.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;
server::server(char* ip,int p){
    ipaddress=ip;
    port=p;
}
int server::socket_bind(){
    int listenfd;
    sockaddr_in servaddr;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"create socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
		exit(1);
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
    inet_pton(AF_INET,ipaddress,&servaddr.sin_addr);
	servaddr.sin_port=htons(port);

	if(bind(listenfd,(sockaddr*)&servaddr,sizeof(servaddr))==-1){
		cout<<"bind socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
		exit(1);
	}
    return listenfd;
}