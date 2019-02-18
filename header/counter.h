#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "counter";
    }
};

#endif /* COUNTER_H */
