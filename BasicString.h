#ifndef PROJ25_STRINGCLASS_H
#define PROJ25_STRINGCLASS_H
#include <string>
#include "vector"
using namespace std;



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