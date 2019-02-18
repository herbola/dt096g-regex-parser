#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"


struct substitute : op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "substitute";
    }
};

#endif /* SUBSTITUTE_H */