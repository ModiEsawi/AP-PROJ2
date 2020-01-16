
#ifndef EX4_ADAPTER_H
#define EX4_ADAPTER_H

#include "Solver.h"
#include "ISearcher.h"


template<typename Problem, typename T,typename  Solution>

class Adapter : public Solver<Problem,Solution>{

private:

    ISearcher<T,Solution>* is;

public:
    //Constructor
    explicit Adapter(ISearcher<T,Solution>* is):is(is){}

    //Adaption
    Solution* solve(Problem* problem) {
        return is->search(problem);
    }
    ~Adapter(){
        delete is;
    }
};

#endif //EX4_ADAPTER_H
