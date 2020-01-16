#ifndef PROJ25_STRINGCLASS_H
#define PROJ25_STRINGCLASS_H
#include <string>
using namespace std;



class BasicString {
private:
    string str;
public:
    //Constructor
    BasicString(string s){this->str=s;}

    //representable
    string toString() const{
        return this->str;
    }
};


#endif