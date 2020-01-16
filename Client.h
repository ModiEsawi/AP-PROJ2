#ifndef EX4_CLIENT_H
#define EX4_CLIENT_H

#include <string>
#include "GeneralSocket.h"

class Client {
    generalSocket socket;
public:

    Client() = default;
    explicit Client(generalSocket sock) : socket(sock) {}
    string read(int number);
    void write(string line);
    void setTimeout(int sec, int usec = 0) {
        this->socket.setTimeout(sec, usec);
    }
    void close() { this->socket.close(); }
};



#endif //EX4_CLIENT_H
