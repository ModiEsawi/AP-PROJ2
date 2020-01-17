
#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <map>
#include "Searcher.h"
#include <unordered_set>
#include "pthread.h"
pthread_mutex_t lock2;
template<typename Problem, typename Solution>
class Astar : public Searcher<Problem, Solution> {
    Solution *search(ISearchable<Problem> *searchable) {

        State<Problem> *goalIsFound = NULL;
        string stringSolution;

        State<Problem> *initialState = searchable->getInitialState();


        unordered_set < State<Problem> * > closedHashSet;

        State<Problem> *finalGoal = searchable->getGoalState();
        int goalX = finalGoal->getState().getX();
        int goalY = finalGoal->getState().getY();

        int initialX = initialState->getState().getX();
        int initialY = initialState->getState().getY();

        double initialHfunction = abs(initialX - goalX) + abs(initialY - goalY);

        double initialFfunction = initialHfunction;

        initialState->setThePathCost(initialState->getCost());
        initialState->setTheFcost(initialFfunction);

        this->starPriorityQueue.push(initialState);

        while (!this->starPriorityQueue.empty()) {
            State<Problem> *currentState = this->starPopOpenList();

            closedHashSet.insert(currentState);

            if (*currentState == *finalGoal) {
                goalIsFound = currentState;
                break;
            }

            vector<State<Problem> *> successors = searchable->getAllPossibleStates(currentState);
            typename vector<State<Problem> *>::iterator it;
            for (it = successors.begin(); it != successors.end(); ++it) {
                State<Problem> *successor = *it;

                typename unordered_set<State<Problem> *>::iterator closedSetIterator;

                bool foundInCloseSet = false;

                for (closedSetIterator = closedHashSet.begin();
                     closedSetIterator != closedHashSet.end(); ++closedSetIterator) {
                    if (*successor == *(*closedSetIterator))
                        foundInCloseSet = true;
                }
                double gFunction = currentState->getPathCost() + successor->getCost();

                int successorsX = successor->getState().getX();
                int successorsY = successor->getState().getY();

                double hFunction = abs(successorsX - goalX) + abs(successorsY - goalY);

                double fFunction = gFunction + hFunction;

                if(!foundInCloseSet && !this->starCheckExistence(successor)){
                    successor->setWhereWeCameFrom(currentState);
                    successor->setThePathCost(gFunction);
                    successor->setTheFcost(fFunction);
                    this->starPriorityQueue.push(successor);
                } else{
                    if (foundInCloseSet){
                        continue;
                    }
                    else if (gFunction < successor->getPathCost()){
                        successor->setWhereWeCameFrom(currentState);
                        successor->setThePathCost(gFunction);
                        successor->setTheFcost(fFunction);
                        this->starPriorityQueue.push(successor);
                        this->starAdjustSmallerPath(successor,currentState);
                    }
                }
            }
        }

        if (goalIsFound != NULL) {
            vector<State<Problem> *> fathers = this->traceBack(goalIsFound);
            if (fathers.size() == 1) {
                stringSolution = "Not Found";
                this->totalPathCost = -1;

            } else {
                State<Problem> *loopVar = goalIsFound;
                this->totalPathCost += goalIsFound->getCost();

                // get each father node cost and add it to the sum of the path

                while (loopVar->getWhereWeCameFrom() != NULL) {
                    loopVar = loopVar->getWhereWeCameFrom();
                    this->totalPathCost += loopVar->getCost();
                }
                typename vector<State<Problem> *>::iterator it = fathers.begin();
                fathers.insert(it, goalIsFound);
                stringSolution = searchable->getFullPathAsString(fathers);
            }
        } else {
            stringSolution = "Not Found";
            this->totalPathCost = -1;
        }
        // now we will build a solution from what we get as a final goal state.

        auto finalSolution = new Solution(stringSolution);


        return finalSolution;
    }

    ISearcher<Problem,Solution>* getClone(){
        return new Astar();
    }
};


#endif //EX4_ASTAR_H
