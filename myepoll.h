void add_event(int epolllfd,int fd,int state);
void del_event(int epolllfd,int fd,int state);
void mod_event(int epolllfd,int fd,int state);
void do_read(int epollfd,int fd,char* buf);
void do_write(int epollfd,int fd,char* buf);
void handle_accept(int epollfd,int listenfd);
void handle_events(int epollfd,struct epoll_event* events,int num,int listenfd,char* buf);
void do_epoll(int listenfd);
