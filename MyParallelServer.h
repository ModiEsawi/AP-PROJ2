#ifndef PROJ25_MYPARALLELSERVER_H
#define PROJ25_MYPARALLELSERVER_H

#include "ClientHandler.h"
#include "GeneralServer.h"
#include <thread>
#include "TimeOutException.h"
#include <sys/socket.h>
#include <netinet/in.h>

/*
 * MyParallelServer class is a server that handle the clients were joined
 * in parallel  and this done by threads .
 * we wait unlimited time to the first client, and then
 * set timeout to stop if no joined until this time.
 */
class MyParallelServer : public GeneralServer {
private:
    short clients;
    bool oneJoined;
    bool canStop;
    bool shouldStop = false;
public:

    //constructor.
    MyParallelServer() : clients(0), oneJoined(false), canStop(false) {}

    //open socket on the given port , handle by the gevin protocol(c)
    void open(int port, server_side::ClientHandler *c) override ;

    void helper(Client client_socket, server_side::ClientHandler *clientHandler) ;


};

#endif