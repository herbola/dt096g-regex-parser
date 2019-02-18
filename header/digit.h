#ifndef DIGIT_H
#define DIGIT_H

#include "op.h"


struct digit : op {
    std::string _id;
    std::string digits = "0123456789";
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return this->_id;
    }
};

#endif /* DIGIT_H */