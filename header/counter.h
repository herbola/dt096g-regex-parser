#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"


struct counter: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "counter";
    }
};

#endif /* COUNTER_H */
