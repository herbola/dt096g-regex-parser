

#ifndef ADDER_H
#define ADDER_H
#include "op.h"

struct adder: op {
    double eval() override {
        return operands[0]->eval() + operands[1]->eval();
    }
};


#endif /* ADDER_H */


