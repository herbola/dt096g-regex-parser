#ifndef ELEMENTARY_RE_H
#define ELEMENTARY_RE_H

#include "op.h"


struct elementary_re: op {
    std::string eval(std::string source){
        return operands[0]->eval(source);
    }
    std::string id() override{
        return "elementary_re";
    }
};

#endif /* ELEMENTARY_RE_H */
