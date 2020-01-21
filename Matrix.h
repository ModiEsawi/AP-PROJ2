#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include <cstring>
#include "ISearchable.h"
#include "Coordinates.h"
#include "vector"

#define WALL -1

using namespace std;

template<typename T>
class Matrix : public ISearchable<T> {
private:
    double **elements; //dynamic two dimensional array
    State<T> *initialState;
    State<T> *finalGoal;
    int rowsNumber;
    int columnNumber;
    vector<string> givenRows;
public:

    Matrix(vector<string> &rows) {
        this->givenRows = rows;
        this->rowsNumber = rows.size() - 2; // the last 2 are goal and start
        int rowCounter = 0;
        bool flag = true, initial = false;
        vector<string>::iterator it;
        for (it = rows.begin(); it != rows.end(); ++it, rowCounter++) {
            string temp, line = *it;
            list<double> values;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] != ',' && line[i] != '\n' && line[i] != ' ')
                    temp += line[i];
                if (line[i] == ',' || line[i] == '\n' || i == line.size() - 1) {
                    values.push_back(atof(temp.c_str()));
                    temp = "";
                }
            }
            //last two lines
            if (next(it, 2) == rows.end() || next(it, 1) == rows.end()) {
                int left = (int) (*values.begin()); //before the ,
                values.pop_front();
                int right = (int) (*values.begin()); //after the ,
                if (!initial) { //first line of the two
                    this->initialState = new State<T>(T(left, right));
                    this->initialState->setTheCost(this->elements[left][right]);
                    this->initialState->setThePathCost(this->elements[left][right]);
                    initial = true;
                } else { //the line that define the goal state
                    this->finalGoal = new State<T>(T(left, right));
                    this->finalGoal->setTheCost(this->elements[left][right]);
                    this->finalGoal->setThePathCost(this->elements[left][right]);
                    break;
                }
                continue;
            }
            if (flag) { //just one time define this
                this->columnNumber = (int) values.size(); //values in one string define a columns num
                this->elements = new double *[this->rowsNumber]; //allocating
                for (int k = 0; k < rowsNumber; k++) { //allocating
                    this->elements[k] = new double[this->columnNumber];
                }
                flag = false;
            }
            list<double>::iterator iter;
            int j = 0;
            //initialize the matrix
            for (iter = values.begin(); iter != values.end(); ++iter, j++) {
                this->elements[rowCounter][j] = *iter;
            }
        }
    }

    //CTOR
    ~Matrix() {
        //delete the matrix
        for (int i = 0; i < rowsNumber; i++) {
            delete[] this->elements[i];
        }
        delete[] this->elements;
        //delete the initial and goal states
        if (this->initialState != NULL) {
            delete this->initialState;
            this->initialState = NULL;
        }
        if (this->finalGoal != NULL) {
            delete this->finalGoal;
            this->finalGoal = NULL;
        }
    }

    //getters
    State<T> *getInitialState() override { return this->initialState; }

    State<T> *getGoalState() override { return this->finalGoal; }

    vector<State<T> *> getAllPossibleStates(State<T> *givenState) override {

        /*
       * may be maximum 4 successors : up ,down ,left,right
       */
        vector<State<T> *> possibleStates;
        T currentState = givenState->getState();
        int x = currentState.getX();
        int y = currentState.getY();

        //down
        if (x + 1 <= rowsNumber - 1 && elements[x + 1][y] != WALL) {
            auto down = new State<T>(T(x + 1, y));
            down->setTheCost(elements[x + 1][y]);
            down->setThePathCost(elements[x + 1][y]);
            possibleStates.push_back(down);
        }
        //up
        if (x - 1 >= 0 && elements[x - 1][y] != WALL) {
            auto up = new State<T>(T(x - 1, y));
            up->setTheCost(elements[x - 1][y]);
            up->setThePathCost(elements[x - 1][y]);

            possibleStates.push_back(up);
        }
        //right
        if (y + 1 <= columnNumber - 1 && elements[x][y + 1] != WALL) {
            auto right = new State<T>(T(x, y + 1));
            right->setTheCost(elements[x][y + 1]);
            right->setThePathCost(elements[x][y + 1]);

            possibleStates.push_back(right);
        }
        //left
        if (y - 1 >= 0 && elements[x][y - 1] != WALL) {
            auto left = new State<T>(T(x, y - 1));
            left->setTheCost(elements[x][y - 1]);
            left->setThePathCost(elements[x][y - 1]);

            possibleStates.push_back(left);
        }

        return possibleStates;

    }

    /*
     * return string of the matrix: format: initiaLEFT,initialRIght,goalLEFT,goalRIGHT,....(VALUES OF MATRIX)
     */
    string toString() const {
        string representedMatrix;
        representedMatrix += to_string(this->initialState->getState().getX());
        representedMatrix += ',';
        representedMatrix += to_string(this->initialState->getState().getY());
        representedMatrix += ',';
        representedMatrix += to_string(this->finalGoal->getState().getX());
        representedMatrix += ',';
        representedMatrix += to_string(this->finalGoal->getState().getY());
        for (int i = 0; i < rowsNumber; i++) {
            for (int j = 0; j < columnNumber; j++) {
                representedMatrix += ',';
                representedMatrix += to_string(elements[i][j]);
            }
        }
        return representedMatrix;
    }

    string getFullPathAsString(vector<State<T> *> path) override {
        reverse(path.begin(), path.end());
        string pathString;
        typename vector<State<T> *>::iterator it;
        for (it = path.begin(); it != path.end(); ++it) {
            string status = "";
            if (++it == path.end()) {
                break;
            }
            --it;
            State<T> *curr = *it;
            ++it;
            State<T> *next = *it;
            it--;
            T currIndex = curr->getState();
            T nextIndex = next->getState();
            string value = to_string(curr->getPathCost());
            if (currIndex.getX() < nextIndex.getX()) {
                status = "Down ";
            } else if (currIndex.getX() > nextIndex.getX()) {
                status = "Up ";
            } else if (currIndex.getY() < nextIndex.getY()) {
                status = "Right ";
            } else {
                status = "Left ";
            }
            pathString += status;
            pathString += ",";

        }
        pathString = pathString.substr(0, pathString.size() - 1); //delete last ','
        return pathString;
    }

    ISearchable<T> *getClone() {
        return new Matrix(this->givenRows);
    }
};


#endif //EX4_MATRIX_H
