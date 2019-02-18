#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"
#include <string>

struct character : op {
    std::string _id;
    std::string eval(std::string source){
        return this->id();
    }
    std::string id() override{
        return this->_id;
    }
};

#endif /* CHARACTER_H */