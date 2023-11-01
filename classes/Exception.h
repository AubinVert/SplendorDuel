#ifndef LO21_SPLENDOR_DUEL_EXCEPTION_H
#define LO21_SPLENDOR_DUEL_EXCEPTION_H
#include <iostream>

class SplendorException{
    std::string info;
public:
    SplendorException(const std::string &str) : info(str){}
    std::string getInfos() const{return info;}
};



#endif //LO21_SPLENDOR_DUEL_EXCEPTION_H
