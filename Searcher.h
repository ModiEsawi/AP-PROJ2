
#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <queue>
#include <vector>
#include "ISearcher.h"
#include "State.h"
#include "algorithm"

template<typename Problem, typename Solution>

/*
 * Searcher abstract class.
 * define methods that common among all the searchers.
 */

class Searcher : public ISearcher<Problem, Solution> {

private:


protected:

    struct Comp2 {
        bool operator()(const State<Problem> *a, const State<Problem> *b) {
            return a->getTheFcost() > b->getTheFcost();
        }
    };

    struct Comp {
        bool operator()(const State<Problem> *a, const State<Problem> *b) {
            return a->getPathCost() > b->getPathCost();
        }
    };

    priority_queue<State<Problem> *, vector<State<Problem> *>, Comp2> starPriorityQueue;

    priority_queue<State<Problem> *, vector<State<Problem> *>, Comp> priorityQueue;


    int evaluatedNodes;
    double totalPathCost;

public:
    Searcher() : evaluatedNodes(0), totalPathCost(0) {}

    int getNumberOfNodesEvaluated() {
        return this->evaluatedNodes;
    }


    vector<State<Problem> *> traceBack(State<Problem> *goalState) {
        vector<State<Problem> *> fathers;
        fathers.push_back(goalState);
        while (goalState->getWhereWeCameFrom() != NULL) {
            fathers.push_back(goalState->getWhereWeCameFrom());
            goalState = goalState->getWhereWeCameFrom();
        }
        return fathers;
    }


    State<Problem> *popOpenList() {
        State<Problem> *temp = this->priorityQueue.top();
        this->priorityQueue.pop();
        this->evaluatedNodes++;
        return temp;
    }

    State<Problem> *starPopOpenList() {
        State<Problem> *temp = this->starPriorityQueue.top();
        this->starPriorityQueue.pop();
        this->evaluatedNodes++;
        return temp;
    }

    bool checkExistence(State<Problem> *stateToLookFor) {

        priority_queue < State<Problem> * , vector<State<Problem> *>, Comp > queueCopy = this->priorityQueue;
        while (!queueCopy.empty()) {  //dequeue
            if (*(queueCopy.top()) == *stateToLookFor) { //contain

                return true;

            }
            queueCopy.pop();
        }

        return false;
    }

    bool starCheckExistence(State<Problem> *stateToLookFor) {
        priority_queue < State<Problem> * , vector<State<Problem> *>, Comp2 > queueCopy = this->starPriorityQueue;
        while (!queueCopy.empty()) {  //dequeue
            if (*(queueCopy.top()) == *stateToLookFor) { //contain
                return true;
            }
            queueCopy.pop();
        }
        return false;

    }

    void adjustSmallerPath(State<Problem> *toAdjust, State<Problem> *father) {
        vector<State<Problem> *> queueVector;
        while (!this->priorityQueue.empty()) {
            queueVector.push_back(this->priorityQueue.top());
            this->priorityQueue.pop();
        }
        typename vector<State<Problem> *>::iterator vectorIterator;
        State<Problem> *foundInOpenList;
        for (vectorIterator = queueVector.begin(); vectorIterator != queueVector.end(); ++vectorIterator) {
            if (*vectorIterator == toAdjust) {
                foundInOpenList = *vectorIterator;
                queueVector.erase(vectorIterator);
                break;
            }
        }
        foundInOpenList->setThePathCost(father->getPathCost() + toAdjust->getCost());
        foundInOpenList->setWhereWeCameFrom(father);

        // after we are done adjusting the element , we will build back the priority queue
        vectorIterator = queueVector.begin();
        for (; vectorIterator != queueVector.end(); ++vectorIterator) {
            this->priorityQueue.push(*vectorIterator);
        }

    }

    void starAdjustSmallerPath(State<Problem> *toAdjust, State<Problem> *father) {
        vector<State<Problem> *> queueVector;
        while (!this->starPriorityQueue.empty()) {
            queueVector.push_back(this->starPriorityQueue.top());
            this->starPriorityQueue.pop();
        }
        typename vector<State<Problem> *>::iterator vectorIterator;
        State<Problem> *foundInOpenList;
        for (vectorIterator = queueVector.begin(); vectorIterator != queueVector.end(); ++vectorIterator) {
            if (*vectorIterator == toAdjust) {
                foundInOpenList = *vectorIterator;
                queueVector.erase(vectorIterator);
                break;
            }
        }
        foundInOpenList->setThePathCost(father->getPathCost() + toAdjust->getCost());
        foundInOpenList->setWhereWeCameFrom(father);

        // after we are done adjusting the element , we will build back the priority queue
        vectorIterator = queueVector.begin();
        for (; vectorIterator != queueVector.end(); ++vectorIterator) {
            this->starPriorityQueue.push(*vectorIterator);
        }

    }

    virtual ~Searcher() {
    }
};

#endif //EX4_SEARCHER_H
