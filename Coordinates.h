
#ifndef EX4_COORDINATES_H
#define EX4_COORDINATES_H

#include "string"

using namespace std;

// X and Y coordinates of the matrix

class Coordinates {
private:

    int x;
    int y;

public:
    //constructor.
    Coordinates(int left, int right) : x(left), y(right) {}

    //default CTOR
    Coordinates() : x(0), y(0) {}

    Coordinates(string givenString) {
        try {
            string temp;
            long flag = 0,size = givenString.size(),i;
            for (i = 0; i < size; i++) { //iterate over each char in the string
                if (givenString[i] != ',') //split by ','
                    temp += givenString[i];
                if (flag == 0 && givenString[i] == ',') { //left
                    flag = 1;
                    this->x = stoi(temp);
                    temp = "";
                } else if (flag == 1 && i == size - 1) { //right
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


    string toString() const { return to_string(x) + "," + to_string(y); }

    // operator overloading

    bool operator==(const Coordinates &i) const {
        return this->x == i.getX() && this->y == i.getY();
    }

};


#endif //EX4_COORDINATES_H
