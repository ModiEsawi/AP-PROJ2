#include <list>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <fstream>
#include <debug/vector>
#include <iostream>
#include "CacheManager.h"
#include <functional>

using namespace std;

/*
 * FileCacheManager class.
 * save the problem and it's solution in file
 *
 * note that the Problem and Solution MUST be representable , which mean that have toString() function that return an
 * appropriate string that define the object , in addition it MUST have a constructor that get string (or list of
 * strings) which means can build the object from a string .
 */
template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:


    list <pair<string, string>> cacheList; // the list that will hold the cache members

    // the cache map that will hold a key and an iterator to the list that will point to each cache member.
    unordered_map<string, typename list<pair<string, string>>::iterator> cacheMap;

    unordered_map<string, string> hashCache; //HashMap ->get solution in O(1) time (if solved before)
public:
    // initializing the objects fields.
    explicit FileCacheManager() {

    }

    void insertSolution(Problem *problem, Solution *solution) {
        hash<std::string> hasher;
        string fileName = to_string(hasher(problem->toString()));
        fstream myfile;

        this->hashCache[problem->toString()] = solution->toString();

//     giving each object its own file! , and a unique name because of the key.

        myfile = std::fstream(fileName, ios_base::app); // creating the file..
        if (!myfile.is_open()) {
            throw "can not create the object file!";
        }
//     Here would be some error handling
        myfile << problem->toString() << "\n";
        myfile << solution->toString() << "\n";

        myfile.close();


    }

    Solution *getSolution(Problem *problem) {

        if (foundInMap(problem)) {
            return new Solution(this->hashCache.find(problem->toString())->second);
        } else if (foundInFiles(problem)) {
            hash<std::string> hasher;
            string fileName = to_string(hasher(problem->toString()));
            fstream myfile;
            myfile.open(fileName, ios::in);
            string line, problemInFile, solution;
            bool flag = false;
            // only 2 lines in each file!
            if (myfile) {
                while (getline(myfile, line)) { //initialize the hash map
                    if (!flag) {
                        problemInFile = line;
                        flag = true;
                    } else {
                        solution = line;
                        this->hashCache.insert(pair<string, string>(problemInFile, solution));
                        flag = false;
                    }
                }
                myfile.close();
            }
            return new Solution(solution);

        }
    }

    // finding out if the matrix was solved before

    bool alreadySolved(Problem *problem) {
        return foundInMap(problem) || foundInFiles(problem);
    }

    // if it is in the map..

    bool foundInMap(Problem *problem) {
        if (this->hashCache.find(problem->toString()) == this->hashCache.end()) {
            return false;
        }
        return true;
    }

    // if it is in the files..

    bool foundInFiles(Problem *problem) {
        hash<std::string> hasher;
        string fileName = to_string(hasher(problem->toString()));
        ifstream isfile(fileName);
        return (bool) isfile;
    }

    //
    virtual CacheManager<Problem, Solution> *getClone() {
        return new FileCacheManager<Problem, Solution>;
    }

};




