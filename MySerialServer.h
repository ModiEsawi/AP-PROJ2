#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <pthread.h>
#include "Server.h"
#include "GeneralServer.h"
#include <thread>

class MySerialServer : public GeneralServer{

public:
    void open (int givenPort ,server_side::ClientHandler *givenClientHandler);
};





#endif //EX4_MYSERIALSERVER_H
