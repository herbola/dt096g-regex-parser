#ifndef PROGRAM_H
#define PROGRAM_H

#include "op.h"


struct program:op {
    double eval(){
        return operands[1]->eval();
    }
    
    std::string id() override{
        return operands[0]->id();
    }
};

#endif /* PROGRAM_H */

