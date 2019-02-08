#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"


struct substitute : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "substitute";
    }
};

#endif /* SUBSTITUTE_H */