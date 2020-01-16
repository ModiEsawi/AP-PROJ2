#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include "Solver.h"
#include "string"
template <typename Problem, typename Solution>
class StringReverser : public Solver<Problem,Solution>{
public:
    Solution* solve(Problem *stringToReverse) override;
};



#endif //EX4_STRINGREVERSER_H
