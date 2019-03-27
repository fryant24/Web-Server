class server{
public:
    server(char* ipaddress,int port);
    ~server(){};
    int socket_bind();
private:
    char* ipaddress;
    int port;
};