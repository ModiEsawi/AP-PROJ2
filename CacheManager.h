#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<typename Problem, typename Solution>


/*
 * CacheManager Interface.
 * saves the solution of given problem
 *
* note that the Problem and Solution MUST be representable ,
* which mean that have toString() function that return an
* appropriate string that define the object , in addition
* it MUST have a constructor that get string (or list of strings) which means
* can build the object from a string .
*
*/

class CacheManager {
public:
    virtual Solution* getSolution(Problem* problem) = 0;

    virtual bool alreadySolved(Problem* problem) = 0;

    virtual void insertSolution(Problem* problem, Solution* solution) = 0;

    virtual CacheManager<Problem,Solution>* getClone()=0;

    virtual ~CacheManager() {}
};


#endif //EX4_CACHEMANAGER_H
