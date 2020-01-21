#include <sys/socket.h>
#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include "GeneralServer.h"


void GeneralServer::bindToPort(int port) {
    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(socket.socket_fd, (sockaddr *) &addr_in, sizeof(addr_in)) == -1) {
        throw std::system_error(std::error_code(errno, std::generic_category()), "Failed To Bind !");
    }
}

//making the socket listen to the port
void GeneralServer::listen(int maximumAllowedListeners) {
    if (::listen(socket.socket_fd, maximumAllowedListeners) == -1) {
        throw std::system_error(std::error_code(errno, std::generic_category()), "Failed To listen");
    }
    cout << "Server is now listening ..." << std::endl;

}

void GeneralServer::setTimeout(int sec, int uSec) {
    socket.setTimeout(sec, uSec);
}

Client GeneralServer::accept() {

    sockaddr_in address;
    socklen_t len = sizeof(address);
    int client_fd = ::accept(socket.socket_fd, (struct sockaddr *) &address, (socklen_t *) &len);
    if (client_fd < 0) {
        // eagain and ewouldblock are errors normally hapenning on timeouts
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            throw TimeOutException("Timed Out on accept");
        else
            throw std::system_error(std::error_code(errno, std::generic_category()), "Error on accept");
    }

    generalSocket newClientSocket(client_fd);
    newClientSocket.setTimeout(0);

    return (Client) newClientSocket;

}



