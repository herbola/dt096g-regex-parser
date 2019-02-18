#ifndef BLANK_H
#define BLANK_H

#include "op.h"


struct blank : op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "blank_space";
    }
};

#endif /* BLANK_H */