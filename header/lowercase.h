#ifndef LOWERCASE_H
#define LOWERCASE_H

#include "op.h"


struct lowercase: op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "lowercase";
    }
};

#endif /* LOWERCASE_H */
