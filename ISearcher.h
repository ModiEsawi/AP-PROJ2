
#ifndef EX4_ISEARCHER_H
#define EX4_ISEARCHER_H

#include "ISearchable.h"

template<typename Problem, typename Solution>
class ISearcher {
public:
    virtual Solution *search(ISearchable<Problem> *searchable) = 0;

    virtual ISearcher<Problem,Solution>* getClone() = 0;

    int getNumberOfNodesEvaluated() const { return this->evaluatedNodes; }

//    virtual ~ISearcher() = delete;

//    virtual int getPathCost() = 0;
};

#endif //EX4_ISEARCHER_H
