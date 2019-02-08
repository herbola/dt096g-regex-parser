#ifndef SIMPLE_RE_H
#define SIMPLE_RE_H

#include "op.h"


struct simple_re : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "simple_re";
    }
};

#endif /* SIMPLE_RE_H */