#include <sys/socket.h>
#include <unistd.h>
#include "GeneralSocket.h"

generalSocket::generalSocket(int open_sock_fd) {
    this->socket_fd = open_sock_fd;
}

generalSocket::generalSocket() {
    this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        throw "could not create a socket!";
    }

}

void generalSocket::setTimeout(int sec, int usec) {
    struct timeval tv;
    tv.tv_usec = usec;
    tv.tv_sec = sec;
    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv) == -1) {
        throw "Failed with setting the socket time out !";
    }

}

void generalSocket::close() {
    if (::close(this->socket_fd) < 0) {
        throw ("failure on closing socket");
    }
}
