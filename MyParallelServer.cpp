#include "MyParallelServer.h"

void MyParallelServer::open(int port, server_side::ClientHandler *c) {
    //create socket
    int socketfd = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
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
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        exit(0);
    }
    //making socket listen to the port
    if (::listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        exit(0);
    }
    cout << "Server is now listening ..." << std::endl;

    int addrLenn = sizeof(address);

    timeval timeout;
    int client_socket;

    timeout.tv_sec = 120;
    timeout.tv_usec = 0;

    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    while (!shouldStop) {
        timeout.tv_sec = 120;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        client_socket = ::accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrLenn);
        if (client_socket < 0) {
            //timeout
            if (errno == EWOULDBLOCK) {
                stop();
                cout << "Timed Out!" << endl;
                break;
            } else {
                perror("A general error has occurred");
                break;
            }
        }
        generalSocket clientSocket(client_socket);
        thread t(&MyParallelServer::helper, this, (Client) clientSocket, c);
        t.detach();
    }
}

void MyParallelServer::helper(Client client_socket, server_side::ClientHandler *clientHandler) {
    clientHandler->getClone()->handleClient(client_socket);
}
