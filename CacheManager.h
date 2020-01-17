#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<typename Problem, typename Solution>

class CacheManager {
public:
    virtual Solution* getSolution(Problem* problem) = 0;

    virtual bool alreadySolved(Problem* problem) = 0;

    virtual void insertSolution(Problem* problem, Solution* solution) = 0;

    virtual CacheManager<Problem,Solution>* getClone()=0;

//    virtual ~CacheManager() {}
};


#endif //EX4_CACHEMANAGER_H
