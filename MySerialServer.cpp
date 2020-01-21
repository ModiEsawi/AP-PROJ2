#include "MySerialServer.h"
#include "GeneralServer.h"

bool joined = false;
void MySerialServer::open(int givenPort, server_side::ClientHandler *givenClientHandler) {

    bindToPort(givenPort);
    listen(MAX_ALLOWED_LISTENERS);
    joined = false;
    while(true){
        try {
            if (joined){
                setTimeout(TIMEOUT);
            }
            Client client = this->accept();
            givenClientHandler->handleClient(client);
            joined = true;
        }catch (exception e){
            joined = false;
            return;
        }
    }
}
