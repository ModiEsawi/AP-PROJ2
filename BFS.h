
#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "Searcher.h"
#include "queue"

template<typename Problem, typename Solution>
class BFS : public Searcher<Problem, Solution> {
public:
    Solution *search(ISearchable<Problem> *searchable) {
        State<Problem>* goalIsFound = NULL;
        string stringSolution;
        State<Problem> *initialState = searchable->getInitialState();
        queue<State<Problem>*> statesQueue;
        vector<State<Problem> *> visited;

        State<Problem>* initial = searchable->getInitialState();
        statesQueue.push(initial);
        visited.push_back(initial); // mark as visited

        State<Problem> *finalGoal = searchable->getGoalState();

        while (!statesQueue.empty()) {
            // pop from stack
            State<Problem> *atTheTop = statesQueue.front();
            statesQueue.pop();
            if (*atTheTop == *finalGoal) {
                goalIsFound = atTheTop;
                break;
            }
            vector<State<Problem> *> successors = searchable->getAllPossibleStates(atTheTop);
            this->evaluatedNodes++;

            typename vector<State<Problem> *>::iterator successorsIterator;
            for (successorsIterator = successors.begin(); successorsIterator != successors.end(); ++successorsIterator){

                State<Problem> *currentState = *successorsIterator;
                bool alreadyVisited = false;
                for (auto visitedIterator : visited) {
                    if (*currentState == *visitedIterator) { // check later to see if u can add "break" here
                        alreadyVisited = true;
                    }
                }
                if (!alreadyVisited) {
                    currentState->setWhereWeCameFrom(atTheTop);
                    statesQueue.push(currentState);
                    visited.push_back(currentState);
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
                stringSolution = searchable->getFullPathAsString(fathers);
            }
        } else {
            stringSolution = "Not Found";
            this->totalPathCost = -1;
        }

        // now we will build a solution from what we get as a final goal state.

        auto finalSolution = new Solution(stringSolution);
        cout<<"Ev ="<<this->evaluatedNodes<<"Cost="<<this->totalPathCost<<endl;
        return finalSolution;
    }
    ISearcher<Problem,Solution>* getClone(){
        return new BFS();
    }

};


#endif //EX4_BFS_H
