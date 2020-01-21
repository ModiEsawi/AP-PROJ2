#ifndef EX4_MAIN_H
#define EX4_MAIN_H

#include <iostream>
#include <string>

#include "StringReverser.h"
#include "FileCacheManager.h"
#include "CacheManager.h"
#include "MyTestClientHandler.h"
#include "Matrix.h"
#include "Coordinates.h"
#include "MySerialServer.h"
#include "Server.h"
#include "Astar.h"
#include "FinalClientHandler.h"
#include "Adapter.h"
#include "BasicString.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "BFS.h"
#include "MyParallelServer.h"

namespace server_side {
    namespace boot {
        class Main {
        public:
            int main(int argc, char *argv[]) {
                int port = 5600;
                if (argv[1] != nullptr) {
                    port = atoi(argv[1]);
                }
                Server *server = new MyParallelServer;
                CacheManager<Matrix<Coordinates>, BasicString> *cacheManager = new FileCacheManager<Matrix<Coordinates>,
                        BasicString>;
                Solver<Matrix<Coordinates>, BasicString> *solver = new Adapter<Matrix<Coordinates>, Coordinates,
                BasicString>(new Astar<Coordinates, BasicString>);
                ClientHandler *clientHandler = new FinalClientHandler<Matrix<Coordinates>, BasicString>
                        (solver,cacheManager);
                server->open(port, clientHandler);
                return 0;
            }
        };
    }
}


#endif //EX4_MAIN_H
