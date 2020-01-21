#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"
#include "TimeOutException.h"

#define MAX_ALLOWED_LISTENERS 5


/*
* Server Class.
* open socket on the given port , dealing with the clients requests by protocol define in clientHandler
*/


namespace server_side {
    class Server {
    public:
        // opens a Server and waits for clients.
        virtual void open(int givenPort, server_side::ClientHandler *givenClientHandler) = 0;

        // stops the Server.

        virtual void stop() = 0;

        virtual ~ Server() = default;
    };


}


#endif //EX4_SERVER_H
