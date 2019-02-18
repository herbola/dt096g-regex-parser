#ifndef BLANK_H
#define BLANK_H

#include "op.h"


struct blank : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "blank";
    }
};

#endif /* BLANK_H */