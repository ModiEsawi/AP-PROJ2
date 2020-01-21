#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <pthread.h>
#include "Server.h"
#include "GeneralServer.h"
#include <thread>


/*
 * MySerialServer class is a server that handle the clients one after the other (queue)
 * we wait unlimited time to the first client, and then set timeout to other clients to join.
 */

class MySerialServer : public GeneralServer{

public:
    void open (int givenPort ,server_side::ClientHandler *givenClientHandler);
};





#endif //EX4_MYSERIALSERVER_H
