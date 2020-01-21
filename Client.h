#ifndef EX4_CLIENT_H
#define EX4_CLIENT_H

#include <string>
#include "GeneralSocket.h"

/*
 * Client class
 * used to communicate with he client .
 * */
class Client {
    generalSocket socket;
public:

    Client() = default;

    void setTimeout(int sec, int usec = 0) {
        this->socket.setTimeout(sec, usec);
    }

    string read(int number);

    void write(string line);

    explicit Client(generalSocket sock) : socket(sock) {}

    void close() { this->socket.close(); }
};


#endif //EX4_CLIENT_H
