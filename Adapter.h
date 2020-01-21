
#ifndef EX4_ADAPTER_H
#define EX4_ADAPTER_H

#include "Solver.h"
#include "ISearcher.h"

/*
 * Adapter is an implementation of Adapter design patterns which links between ISearcher class and Solver Class by
 * containing a member of ISearcher (given by the Constructor) and call ISearcher->search in the solve function .
 */
template<typename Problem, typename T,typename  Solution>

class Adapter : public Solver<Problem,Solution>{

private:

    ISearcher<T,Solution>* is;

public:

     explicit Adapter(ISearcher<T,Solution>* isearcher):is(isearcher){}


    Solution* solve(Problem* problem) {
        return is->search(problem);
    }


    virtual Adapter* getClone(){
        return new Adapter(this->is->getClone());
    }
};

#endif //EX4_ADAPTER_H
