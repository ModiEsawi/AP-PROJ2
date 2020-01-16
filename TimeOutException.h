#ifndef PROJ25_TIMEOUTEXCEPTION_H
#define PROJ25_TIMEOUTEXCEPTION_H

#include <iostream>
/*
 * Timeout Exception , used to define exceptions while
 *  accept in socket
 */
class TimeOutException : public std::runtime_error {
public:
    explicit TimeOutException(std::string &msg) : std::runtime_error(msg){}
    explicit TimeOutException(const char* msg) : std::runtime_error(msg){}
};




#endif