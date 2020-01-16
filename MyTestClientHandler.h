
#ifndef PROJ25_MYTESTCLIENTHANDLER_H
#define PROJ25_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"



template <typename Problem, typename Solution>
class MyTestClientHandler :public server_side::ClientHandler {

private:
    Solver<Problem, Solution> *problemSolver;
    CacheManager<Problem, Solution> *cacheManager;
public:

    //Constructor
    MyTestClientHandler(Solver<Problem, Solution> *solver, CacheManager<Problem, Solution> *cm) : problemSolver(solver),
    cacheManager(cm) {}

    //handle client requests
    void handleClient(Client client) {
        string stringProblem;

        while (stringProblem != "end\n") {

            stringProblem = client.read(1024);
//            Problem clientProblem(stringProblem);
//            if (cacheManager->alreadySolved(stringProblem)) {
//                client.write(cacheManager->getSolution(stringProblem));
//            }
            Solution solutionToProblem = this->problemSolver->solve(stringProblem);
//            this->cacheManager.insertSolution(stringProblem, solutionToProblem);
            client.write(solutionToProblem);
        }

    }
};

#endif