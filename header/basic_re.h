#ifndef BASIC_RE_H
#define BASIC_RE_H

#include "op.h"


struct basic_re : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "basic_re";
    }
};

#endif /* BASIC_RE_H */
