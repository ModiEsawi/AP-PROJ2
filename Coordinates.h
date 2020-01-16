
#ifndef EX4_COORDINATES_H
#define EX4_COORDINATES_H

#include "string"

using namespace std;

class Coordinates {
private:

    int x;
    int y;

public:
    //default CTOR
    Coordinates() : x(0), y(0) {}

    //constructor.
    Coordinates(int left, int right) : x(left), y(right) {}

    Coordinates(string givenString) {
        try {
            string temp;
            int flag = 0;
            for (int i = 0; i < givenString.size(); i++) { //iterate over each char in the string
                if (givenString[i] != ',') //split by ','
                    temp += givenString[i];
                if (flag == 0 && givenString[i] == ',') { //left
                    flag = 1;
                    this->x = stoi(temp);
                    temp = "";
                } else if (flag == 1 && i == givenString.size() - 1) { //right
                    this->y = stoi(temp);
                    temp = "";
                    flag = 2;
                }

            }
        } catch (exception &e) {
            throw ("invalid syntax of index!");
        }
    }

    //setters
    void setX(int left) { this->x = left; }

    void setY(int right) { this->y = right; }

    //getters
    int getX() const { return x; }

    int getY() const { return y; }

    //representable
    string toString() const { return to_string(x) + "," + to_string(y); }

    //operators overloading
    bool operator==(const Coordinates &i) const {
        return this->x == i.getX() && this->y == i.getY();
    }

};


#endif //EX4_COORDINATES_H
