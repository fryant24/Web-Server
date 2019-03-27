#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "getTime.h"
#include "server.h"
#include <cstring>

#define MAXLINE 4096

using namespace std;
int main(int argc,char** arcv){
	int listenfd,connfd,n;
	int port=6666;
	char* ipaddress="192.168.200.145";
	char* buff=new char[MAXLINE];
	char* sendbf=new char[MAXLINE];
	char* stime=new char[50];

	server myserver(ipaddress,port);
	listenfd=myserver.socket_bind();

	if(listen(listenfd,10)==-1){
		cout<<"listen socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
		return 0;
	}

	cout<<"=====waiting for client's request====="<<endl;

	if((connfd=accept(listenfd,(sockaddr*)NULL,NULL))==-1){
                        cout<<"accept socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
        }

	while(1){
		n=read(connfd,buff,MAXLINE);
		if(n>0){
			buff[n]='\0';
			cout<<"recieve msg from client: "<<buff<<endl;
			getTime(stime);
			strcpy(sendbf,"server recv! time is ");
			strcat(sendbf,stime);
			write(connfd,sendbf,strlen(sendbf));
		}
		else if(n==0){
			continue;
		}
		else{
			cout<<"read error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
                	return 0;
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
}
