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
namespace server_side{
    namespace boot{
        class Main{
        public:
            int main(int argc,char* argv[]){
                Server* server = new MySerialServer;
                CacheManager<Matrix<Coordinates>,BasicString>* cacheManager = new FileCacheManager<Matrix<Coordinates>,BasicString>;
                Solver<Matrix<Coordinates>,BasicString> *solver = new Adapter<Matrix<Coordinates>,Coordinates,BasicString>(new Astar
                        <Coordinates,BasicString>);
                ClientHandler* clientHandler = new FinalClientHandler<Matrix<Coordinates>,BasicString>(solver,cacheManager);
                server->open(stoi(argv[1]),clientHandler);
                server->stop();
                return 0;
            }
        };
    }
}
//CacheManager<MazeDomain<Index>,StringClass> *cm=new FileCacheManager<MazeDomain<Index>,StringClass>;
//Solver<MazeDomain<Index>,StringClass> *solver;
//solver= new SolverSearcher<MazeDomain<Index>,Index,StringClass>(new AstarAlgorithm
//<Index,StringClass> );
//ClientHandler* ch=new MyClientHandler<MazeDomain<Index>,StringClass>(solver,cm);
//server->open(stoi(argv[1]),ch);
//server->stop();
//delete solver;
//delete cm;
//delete ch;
//delete server;




#endif //EX4_MAIN_H
