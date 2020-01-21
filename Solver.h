#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

using namespace std;
template <typename Problem, typename Solution>

/*
 * Solver Class .
 * get to classes (replaced with templates) this function must be representable which mean must implement toString
 * function and must have constructor thar get string
 */


class Solver{

public:
    virtual Solution* solve (Problem* problem) = 0;

    virtual Solver* getClone()=0;


    virtual ~ Solver()= default;

};




#endif //EX4_SOLVER_H
