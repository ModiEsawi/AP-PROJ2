
#ifndef EX4_ADAPTER_H
#define EX4_ADAPTER_H

#include "Solver.h"
#include "ISearcher.h"


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
