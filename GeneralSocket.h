
#ifndef EX4_GENERALSOCKET_H
#define EX4_GENERALSOCKET_H

using namespace std;


struct generalSocket{
    int socket_fd;

    explicit generalSocket(int open_sock_fd);

    generalSocket();

    void close();

    void setTimeout(int sec, int usec=0) ;
};


#endif //EX4_GENERALSOCKET_H
