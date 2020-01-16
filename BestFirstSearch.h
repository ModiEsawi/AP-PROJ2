#ifndef EX4_BESTFIRSTSEARCH_H
#define EX4_BESTFIRSTSEARCH_H

#include <unordered_set>
#include "Searcher.h"

template<typename Problem, typename Solution>
class BestFirstSearch : public Searcher<Problem, Solution> {
public:
    Solution *search(ISearchable<Problem> *searchable) {
        State<Problem>* goalIsFound = NULL;
        string stringSolution;
        State<Problem> *initialState = searchable->getInitialState();

        this->priorityQueue.push(initialState);
        initialState->setThePathCost(initialState->getCost());
        unordered_set<State<Problem>*> closedHashSet;

        while (!this->priorityQueue.empty()) {

            State<Problem> *n = this->popOpenList();
            closedHashSet.insert(n);
            State<Problem> *finalGoal = searchable->getGoalState();
            if (*n == *finalGoal) {
                goalIsFound = n;
                break;

            }


            // create a solution from the fathers
            vector<State<Problem> *> successors = searchable->getAllPossibleStates(n);
            typename vector<State<Problem> *>::iterator successorsIterator;
            for (successorsIterator = successors.begin(); successorsIterator != successors.end(); ++successorsIterator){

                State<Problem> *currentState = *successorsIterator;
                double pathCostIncludingSuccessor = n->getPathCost() + currentState->getCost();
                typename unordered_set<State<Problem>*>::iterator closedSetIterator;

                bool foundInCloseSet = false;

                for(closedSetIterator=closedHashSet.begin();closedSetIterator!=closedHashSet.end();++closedSetIterator){
                    if(*currentState == *(*closedSetIterator))
                        foundInCloseSet=true;
                }

                if (!this->checkExistence(currentState) && !foundInCloseSet) {

                    currentState->setWhereWeCameFrom(n);
                    currentState->setThePathCost(pathCostIncludingSuccessor);
                    this->priorityQueue.push(currentState);

                } else if (pathCostIncludingSuccessor < currentState->getPathCost()) {
                    if (!this->checkExistence(currentState)) {
                        this->priorityQueue.push(currentState);

                    } else if (this->checkExistence((currentState))) {
                        this->adjustSmallerPath(currentState, n);
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
                typename vector<State<Problem> *>::iterator it = fathers.begin();
                fathers.insert(it,goalIsFound);
                stringSolution = searchable->getFullPathAsString(fathers);
                this->totalPathCost = goalIsFound->getPathCost();

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

#endif //EX4_BESTFIRSTSEARCH_H
