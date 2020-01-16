#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

using namespace std;
template <typename Problem, typename Solution>

class Solver{

public:
    virtual Solution* solve (Problem* problem) = 0;

    virtual ~ Solver()= default;

};




#endif //EX4_SOLVER_H
