
#ifndef EX4_GENERALSOCKET_H
#define EX4_GENERALSOCKET_H

using namespace std;


/*
 * struct defining general socket, with general operations (open and close)
 * opening is done in the constructor. the socket is not automatically closed in the destructor so that the object
 * can be passed as a parameter (possibly to another thread)
 */


struct generalSocket{
    int socket_fd;

    explicit generalSocket(int open_sock_fd);

    generalSocket();

    void close();

    void setTimeout(int sec, int usec=0) ;
};


#endif //EX4_GENERALSOCKET_H
