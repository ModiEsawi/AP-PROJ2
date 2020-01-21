#ifndef EX4_GENERALSERVER_H
#define EX4_GENERALSERVER_H

#include "Server.h"
#include "GeneralSocket.h"
#include "Client.h"
#include "ClientHandler.h"

#define TIMEOUT 2

class GeneralServer : public server_side::Server {
    generalSocket socket;
    bool shouldStop = false;
public:

    void bindToPort(int port);

    void listen(int maxAllowedListens);

    void setTimeout(int sec, int uSec = 0);

    Client accept();

    void stop() {
        this->shouldStop = true;
        this->socket.close();
    };


    virtual void open(int port, server_side::ClientHandler *givenClientHandler) = 0;
};


#endif //EX4_GENERALSERVER_H
