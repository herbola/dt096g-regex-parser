#ifndef PLUS_H
#define PLUS_H

#include "op.h"


struct plus : op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "plus";
    }
};

#endif /* PLUS_H */