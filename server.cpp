#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "getTime.h"

#define MAXLINE 4096

using namespace std;
int main(int argc,char** arcv){
	int listenfd,connfd,n;
	sockaddr_in servaddr;
	char* buff=new char[MAXLINE];
	char* sendbf=new char[MAXLINE];
	char* stime=new char[50];
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		cout<<"create socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
		return 0;
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(6666);

	if(bind(listenfd,(sockaddr*)&servaddr,sizeof(servaddr))==-1){
		cout<<"bind socket error: "<<strerror(errno)<<"(errno:"<<errno<<")"<<endl;
		return 0;
	}

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
