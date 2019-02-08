#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"


struct character : op {
    std::string _id;
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return this->_id;
    }
};

#endif /* CHARACTER_H */