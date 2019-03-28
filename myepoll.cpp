#include "myepoll.h"
#include "getTime.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#define EPOLLEVENTS 100
#define MAXSIZE 4096
#define FDSIZE 1000
using namespace std;
void add_event(int epollfd,int fd,int state){
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=state;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
}
void del_event(int epollfd,int fd,int state){
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=state;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}
void mod_event(int epollfd,int fd,int state){
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=state;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}
void do_read(int epollfd,int fd,char* buf){
    int nread;
    nread=read(fd,buf,MAXSIZE);
    if(nread==-1){
        perror("read error:");
        close(fd);
        del_event(epollfd,fd,EPOLLIN);
    }
    else if(nread==0){
        fprintf(stderr,"client close.\n");
        close(fd);
        del_event(epollfd,fd,EPOLLIN);
    }
    else{
        char* stime=new char[50];
        cout<<"recv from client: "<<buf<<endl;
        //mod_event(epollfd,fd,EPOLLOUT);
        getTime(stime);
		strcpy(buf,"server recv! time is ");
		strcat(buf,stime);
		mod_event(epollfd,fd,EPOLLOUT);
    }
}
void do_write(int epollfd,int fd,char* buf){
    int nwrite;
    nwrite=write(fd,buf,MAXSIZE);
    if(nwrite==-1){
        perror("write error:");
        close(fd);
        del_event(epollfd,fd,EPOLLOUT);
    }
    else{
        mod_event(epollfd,fd,EPOLLIN);
    }
    memset(buf,0,MAXSIZE);
}
void handle_accept(int epollfd,int listenfd){
    int clifd;
    sockaddr_in cliaddr;
    socklen_t cliaddrlen=sizeof(cliaddr);
    clifd=accept(listenfd,(sockaddr*)&cliaddr,&cliaddrlen);
    if(clifd==-1){
        perror("accept error:");
    }
    else{
        char* ip=inet_ntoa(cliaddr.sin_addr);
        cout<<"a new client connected: "<<ip<<":"<<cliaddr.sin_port<<endl;
        add_event(epollfd,clifd,EPOLLIN);
    }
}
void handle_events(int epollfd,struct epoll_event* events,int num,int listenfd,char* buf){
    int fd;
    for(int i=0;i<num;i++){
        fd=events[i].data.fd;
        if((fd==listenfd)&&(events[i].events & EPOLLIN)){
            handle_accept(epollfd,listenfd);
        }
        else if(events[i].events & EPOLLIN){
            do_read(epollfd,fd,buf);
        }
        else if(events[i].events & EPOLLOUT){
            do_write(epollfd,fd,buf);
        }
    }
}
void do_epoll(int listenfd){
    int epollfd;
    epoll_event events[EPOLLEVENTS];
    int ret;
    char buf[MAXSIZE];
    memset(buf,0,MAXSIZE);
    //创建一个描述符
    epollfd=epoll_create(FDSIZE);
    //添加监听连接事件
    add_event(epollfd,listenfd,EPOLLIN);
    while(1){
        //处理通知的事件
        ret=epoll_wait(epollfd,events,EPOLLEVENTS,-1);
        handle_events(epollfd,events,ret,listenfd,buf);
    }
    close(epollfd);
}
