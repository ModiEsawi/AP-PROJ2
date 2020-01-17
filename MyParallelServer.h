#ifndef PROJ25_MYPARALLELSERVER_H
#define PROJ25_MYPARALLELSERVER_H

#include "ClientHandler.h"
#include "GeneralServer.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include "pthread.h"
pthread_mutex_t lock;
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
    bool shouldStop = false;
public:

    //constructor.
    MyParallelServer() : clients(0),oneJoined(false),canStop(false) {}

    //open socket on the given port , handle by the gevin protocol(c)
    void open(int port, server_side::ClientHandler *c) override{
        //create socket
        int socketfd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (socketfd == -1) {
            //error
            std::cerr << "Could not create a socket"<<std::endl;
            exit(0);
        }

        //bind socket to IP address
        // we first need to create the sockaddr obj.
        sockaddr_in address; //in means IP4
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
        address.sin_port = htons(port);
        //we need to convert our number
        // to a number that the network understands.

        //the actual bind command
        if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
            std::cerr<<"Could not bind the socket to an IP"<<std::endl;
            exit(0);
        }
        //making socket listen to the port
        if (::listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
            std::cerr<<"Error during listening command"<<std::endl;
            exit(0);
        }
        int addrLenn = sizeof(address);

        timeval timeout;
        int client_socket;
        //rememeber to set to 2 mins
        timeout.tv_sec = 120;
        timeout.tv_usec = 0;

        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

        while(!shouldStop){
            //cout<<"inside whil"<<endl;
            timeout.tv_sec = 120;
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
            client_socket=::accept(socketfd, (struct sockaddr *)&address,(socklen_t*)&addrLenn);
            // cout<<client_socket<<endl;
            if (client_socket < 0) {
                //timeout
                if (errno == EWOULDBLOCK) {
                    stop();
                    cout << "timeout!" << endl;
                    break;
                }
                else {
                    perror("other error");
                    break;
                }
            }
            generalSocket clientSocket (client_socket);
            thread t(&MyParallelServer::helper ,this,(Client)clientSocket,c);
            t.detach();

        }
    }

    void helper(Client client_socket, server_side::ClientHandler *clientHandler) {
        clientHandler->getClone()->handleClient(client_socket);

    }




};

#endif