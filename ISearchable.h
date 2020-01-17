
#ifndef EX4_ISEARCHABLE_H
#define EX4_ISEARCHABLE_H

#include <string>
#include "list"
#include "State.h"
#include "vector"
using namespace std;

template<typename T>
class ISearchable {
public:
    virtual State<T> *getInitialState() = 0;

    virtual State<T> *getGoalState() = 0;

    virtual string getFullPathAsString( vector<State<T> *>) = 0;

    virtual vector<State<T>*> getAllPossibleStates(State<T>* givenState) = 0;

    virtual ISearchable* getClone() = 0;


    virtual ~ISearchable()= default;
};


#endif //EX4_ISEARCHABLE_H
