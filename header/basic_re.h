#ifndef BASIC_RE_H
#define BASIC_RE_H

#include "op.h"


struct basic_re : op {
    std::string eval(std::string source){
        return operands[0]->eval(source);
    }
    std::string id() override{
        return "basic_re";
    }
};

#endif /* BASIC_RE_H */
