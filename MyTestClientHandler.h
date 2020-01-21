
#ifndef PROJ25_MYTESTCLIENTHANDLER_H
#define PROJ25_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
/*
 * MyTestClientHandler class. get a problem from the client , (one line) represenented as string,
 * and solve it and return the solution as string back to the client. repeat this operation until recive "end" string
 * from the client. note that the Problem and Solution MUST be representable , which mean that have toString() function
 * that return an appropriate string that define the object , in addition it MUST have a constructor that get string
 * which means can build the object from a string .
 * we Solve the problem and save the solution in the  FIleCacheManger
 * that we received in the constructor.
 */


template<typename Problem, typename Solution>
class MyTestClientHandler : public server_side::ClientHandler {

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

        while (true) {
            string input;
            input = client.read(1024); //get line from the client
            if (input[input.size() - 1] == '\n') //delete new line char if was
                input = input.substr(0, input.size() - 1);
            if (input == "end") {  //stop the contact
                return;
            }
            Problem *problem(input); //build the problem from the string
            if (this->cacheManager->alreadySolved(problem)) { //solved before
                Solution solution = this->cacheManager->getSolution(problem); //get solution
                client.write(solution.toString()); //build string that define the solution
            } else {
                Solution *solution = this->problemSolver->solve(problem); //solve the problem
                this->cacheManager->insertSolution(problem, solution); //save it
                client.write(solution->toString()); //send a string that define the solution
            }

        }

    }

    virtual MyTestClientHandler *getClone() {
        return new MyTestClientHandler(this->problemSolver->getClone(), this->cacheManager->getClone());
    }
};

#endif