
#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "stack"
#include "Searcher.h"

template<typename Problem, typename Solution>
class DFS : public Searcher<Problem, Solution> {

public:

    Solution *search(ISearchable<Problem> *searchable) {
        State<Problem> *goalIsFound = NULL;
        string stringSolution;
        State<Problem> *initialState = searchable->getInitialState();
        stack<State<Problem>*> statesStack;
        vector<State<Problem> *> visited;

        State<Problem>* initial = searchable->getInitialState();
        statesStack.push(initial);
        visited.push_back(initial); // mark as visited

        State<Problem> *finalGoal = searchable->getGoalState();
        while (!statesStack.empty()) {

            // pop from stack
            State<Problem> *atTheTop = statesStack.top();
            statesStack.pop();
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
                    statesStack.push(currentState);
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

        return finalSolution;
    }
};

#endif //EX4_DFS_H
