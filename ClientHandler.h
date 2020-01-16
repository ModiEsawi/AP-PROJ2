#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include "Solver.h"
#include "Client.h"
namespace server_side {
    class ClientHandler {
    public:

        virtual void handleClient(Client client) = 0;

        virtual ~ ClientHandler() = default;
    };
}



#endif //EX4_CLIENTHANDLER_H
