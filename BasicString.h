#ifndef PROJ25_STRINGCLASS_H
#define PROJ25_STRINGCLASS_H
#include <string>
#include "vector"
using namespace std;
/*
 * BasicString class is a class which contain a string ,StringCass is representable which means that
 * we can represent it(toString) and build it from
 * string (constructor)
 */


class BasicString {
private:
    string str;
public:
    //Constructor
    BasicString(string s){this->str=s;}
    BasicString(vector<string> vector){
        this->str = vector[0];
    }
    //representable
    string toString() const{
        return this->str;
    }
};


#endif