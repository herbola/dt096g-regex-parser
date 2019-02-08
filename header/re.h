#ifndef RE_H
#define RE_H

#include "op.h"


struct re : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "re";
    }
};

#endif /* RE_H */
