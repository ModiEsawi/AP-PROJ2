#include <strings.h>
#include <unistd.h>
#include <system_error>
#include <sys/socket.h>
#include "Client.h"
#include "TimeOutException.h"

// reading from the client
string Client::read(int n) {
    char* buffer = new char[n + 1]; //max size is n;
    bzero(buffer,n);
    int read_len =::read(socket.socket_fd, buffer,n); //read from the client
    if (read_len < 0)	{ //problems in receive.
        if (errno == EAGAIN || errno == EWOULDBLOCK)	{
            throw TimeOutException("timeout on read");
        }
        throw system_error(error_code(errno, generic_category()), "error on read");
    }
    std::string output = std::string(buffer);
    delete[] buffer; //free
    return output;
}
// writing to the client
void Client::write(string line) {

    int is_sent = send(this->socket.socket_fd, line.c_str(), (line).size(), 0);
    if (is_sent < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) { // timeout errors
            throw ("timeout on read");
        }
        throw system_error(error_code(errno, generic_category()), "error on read");
    }

}
