#include <list>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <fstream>
#include <debug/vector>
#include <iostream>
#include "CacheManager.h"

using namespace std;


template<typename Problem, typename Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int capacity; // the given cache size.
    int totalItemsInCache; // total items in cache until this moment.

    list<pair<string, string>> cacheList; // the list that will hold the cache members

    // the cache map that will hold a key and an iterator to the list that will point to each cache member.
    unordered_map<string, typename list<pair<string, string>>::iterator> cacheMap;
public:
    // initializing the objects fields.
    explicit FileCacheManager() {
        this->capacity = 5;
        this->totalItemsInCache = 0; // zero items in the beginning
    }

    void insertSolution(Problem key, Solution value){
//    fstream myfile;
//    // giving each object its own file! , and a unique name because of the key.
//    string fileName = key + value;
//    myfile = std::fstream(fileName, ios::binary | ios::out); // creating the file..
//    if (!myfile.is_open()) {
//        throw "can not create the object file!";
//    }
//    //Here would be some error handling                      these two lines should be FIXED!!!!!!!!!!!!
//    myfile << key << "\n";
//    myfile << value << "\n";
////    myfile.write((char *) &value, sizeof(value)); // writing the object to the file
//    myfile.close();
//
//
//    auto iter = this->cacheMap.find(key);
//    if (iter == this->cacheMap.end()) {
//        if (this->totalItemsInCache >= this->capacity) { // if we hit the max capacity..
//            this->cacheMap.erase(this->cacheList.back().first);
//            this->cacheList.pop_back();
//        }
//
//        this->cacheList.push_front({key, value}); // if there is space.. we push it to the front
//        this->cacheMap.insert({key, this->cacheList.begin()});
//        this->totalItemsInCache++; // increasing the total number of members in cache at this moment.
//    } else {
//        // if we only need to update its value .. we will update it and send it to the front.
//        this->cacheList.erase(iter->second);
//        this->cacheList.push_front({key, value});

//    }
}

    Solution getSolution(Problem problem) {
//    auto object = this->cacheMap.find(problem);
//    if (object == cacheMap.end()) { // if the object is not in the cache we look for it in the files system
//        fstream file;
//        string fileName = problem; // what is the file name????????????????????
//        file = fstream(fileName, ios::binary | ios::in | ios::out);
//        if (!file.is_open()) { // if the file i'snt in the file system.
//            throw "Key doesn't exist! please check again";
//        } else {
//            string temp; //  if we found the file is the file system , we will read it from the system and return it.
//            file.read((char *) &temp, sizeof(string));
//            file.close();
//            this->insertSolution(problem, temp);
//            return temp;
//        }
//    }
//    this->insertSolution(problem, object->second->second); // updating the object..
//    return (object->second->second);
}

    bool alreadySolved(Problem problem) {
//    return !(this->cacheMap.find(problem) == this->cacheMap.end());
}


};













//template<typename T>
//void FileCacheManager<T>::foreach(void (*function)(T &)) {
//    // given a lambda function..we will iterate over the members and apply the function on each member.
//    typename list<pair < string, T>>
//    ::iterator
//    it;
//    for (it = cacheList.begin(); it != cacheList.end(); ++it) {
//        function(it->second);
//    }
//}

