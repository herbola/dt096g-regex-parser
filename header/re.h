#ifndef RE_H
#define RE_H

#include "op.h"


struct re : op {
    std::string eval(std::string source){
        return operands[0]->eval(source);
    }
    std::string id() override{
        return "re";
    }
};

#endif /* RE_H */
