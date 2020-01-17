#include <strings.h>
#include <unistd.h>
#include <system_error>
#include <sys/socket.h>
#include "Client.h"
#include "TimeOutException.h"

string Client::read(int size) {

    char buffer[size + 1];
    bzero(buffer, 1024);
    int readSuccessfully = ::read(this->socket.socket_fd, buffer, 4096);
    if (readSuccessfully < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {// timeout errors
            throw TimeOutException("timeout on accept");
        }
        throw std::system_error(std::error_code(errno, std::generic_category()), "error on read");
    }

    return string(buffer);
}

void Client::write(string line) {

    int is_sent = send(this->socket.socket_fd, line.c_str(), (line).size(), 0);
    if (is_sent < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) { // timeout errors
            throw ("timeout on read");
        }
        throw std::system_error(std::error_code(errno, std::generic_category()), "error on read");
    }

}
