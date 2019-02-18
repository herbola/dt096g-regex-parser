#ifndef SIMPLE_RE_H
#define SIMPLE_RE_H

#include "op.h"


struct simple_re : op {
    std::string eval(std::string source){
        return operands[0]->eval(source);
    }
    std::string id() override{
        return "simple_re";
    }
};

#endif /* SIMPLE_RE_H */