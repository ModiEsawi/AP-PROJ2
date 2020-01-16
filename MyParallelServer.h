
#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H
#ifndef PROJ25_MYPARALLELSERVER_H
#define PROJ25_MYPARALLELSERVER_H

#include "ClientHandler.h"
#include "GeneralServer.h"
#include "Client.h"
#include <thread>

#define TIMEOUT 2

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
public:

    //constructor.
    MyParallelServer() : clients(0), oneJoined(false), canStop(false) {}

    //handle client separately
    void startHandle(server_side::ClientHandler *c, Client tp);

    //handle with the clients they joined
    void handle(server_side::ClientHandler *c);

    //open socket on the given port , handle by the gevin protocol(c)
    void open(int port, server_side::ClientHandler *c) override;
};

#endif

#endif //EX4_MYPARALLELSERVER_H
