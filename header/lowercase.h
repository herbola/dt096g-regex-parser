#ifndef LOWERCASE_H
#define LOWERCASE_H

#include "op.h"


struct lowercase: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "lowercase";
    }
};

#endif /* LOWERCASE_H */
