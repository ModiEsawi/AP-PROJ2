
#ifndef EX4_FINALCLIENTHANDLER_H
#define EX4_FINALCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "vector"
#include "BasicString.h"
#include "pthread.h"

/*
 * FinalClientHandler class.
 * get a problem from the client , (one line) represented as string,and solve it and return the solution as string back
 * to the client. repeat this operation until recive "end" string from the client.
 * note that the Problem and Solution MUST be representable , which mean that have toString() function that return an
 * appropriate string that define the object , in addition it MUST have a constructor that get string which means
 * can build the object from a string . we Solve the problem and save the solution by CacheManger
 * that we recieved in contructor.
 */


template<typename Problem, typename Solution>
class FinalClientHandler : public server_side::ClientHandler {
private:
    Solver<Problem, Solution> *problemSolver;
    CacheManager<Problem, Solution> *cacheManager;
public:

    //Constructor
    FinalClientHandler(Solver<Problem, Solution> *solver, CacheManager<Problem, Solution> *cm) : problemSolver(solver),
                                                                                                 cacheManager(cm) {}

    //handle client requests
    void handleClient(Client client) override {

        vector<string> problems;
        string stringProblem;

        while (stringProblem != "end") {

            stringProblem = client.read(1024);
            if (stringProblem[stringProblem.size() - 1] == '\n') { //delete new line char if there was
                stringProblem = stringProblem.substr(0, stringProblem.size() - 1);
            }
            if (stringProblem[stringProblem.size() - 1] == '\r') {
                stringProblem = stringProblem.substr(0, stringProblem.size() - 1);
            }
            problems.push_back(stringProblem); //add the rows to the list

        }
        problems.pop_back();
        auto *problem = new Problem(problems); //build a problem from the list of the strings
        if (this->cacheManager->alreadySolved(problem)) { //solved before
            Solution *sol = this->cacheManager->getSolution(problem); //get the saved solution
            string solutionString = sol->toString(); // build a string solution
            delete sol;
            delete problem;
            client.write(solutionString); //write back to the client
        } else {
            Solution *finalSolution = this->problemSolver->solve(problem); //solve
            string solutionString = finalSolution->toString(); //build a string solution
            this->cacheManager->insertSolution(problem, finalSolution); //save the solution
            delete finalSolution;
            delete problem;

            client.write(solutionString); //write back to the client
        }
    }


    ClientHandler *getClone() {
        return new FinalClientHandler(this->problemSolver->getClone(), this->cacheManager->getClone());
    }
};


#endif //EX4_FINALCLIENTHANDLER_H