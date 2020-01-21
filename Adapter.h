
#ifndef EX4_ADAPTER_H
#define EX4_ADAPTER_H

#include "Solver.h"
#include "ISearcher.h"


template<typename Problem, typename T,typename  Solution>

class Adapter : public Solver<Problem,Solution>{

private:

    ISearcher<T,Solution>* is;

public:

     explicit Adapter(ISearcher<T,Solution>* is):is(is){}


    Solution* solve(Problem* problem) {
        return is->search(problem);
    }
    ~Adapter(){
        delete is;
    }

    virtual Adapter* getClone(){
        return new Adapter(this->is->getClone());
    }
};

#endif //EX4_ADAPTER_H
