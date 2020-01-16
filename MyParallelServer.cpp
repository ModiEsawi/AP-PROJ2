
#include "MyParallelServer.h"

void MyParallelServer::startHandle(server_side::ClientHandler *c, Client tp) {
    c->handleClient(tp);
    this->clients--; //done
    tp.close();
}

void MyParallelServer::handle(server_side::ClientHandler *c) {
    while (true) {
        try {
            if (oneJoined) //set timeout after the first client
                setTimeout(TIMEOUT);
            Client tp = this->accept(); //wait client to join
            this->clients++;
            if (!oneJoined)
                oneJoined = true;
            //handle each client separately
            thread k(&MyParallelServer::startHandle, this, c, tp);
            k.detach(); //continue listening to the next client (parallells)
        } catch (TimeOutException &t) {
            if (clients == 0) { //no more clients and timeout exception throwen
                canStop = true;
                break;
            } else //there are at least one client
                continue;
        }

    }
}

void MyParallelServer::open(int port, server_side::ClientHandler *c) {
    bindToPort(port);
    listen(5);
    thread t(&MyParallelServer::handle, this, c);
    t.detach();
    while (!canStop) {}
}

