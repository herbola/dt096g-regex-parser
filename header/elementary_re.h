#ifndef ELEMENTARY_RE_H
#define ELEMENTARY_RE_H

#include "op.h"


struct elementary_re: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "elementary_re";
    }
};

#endif /* ELEMENTARY_RE_H */
