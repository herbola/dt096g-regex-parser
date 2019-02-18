#ifndef GROUP_H
#define GROUP_H

#include "op.h"


struct group: op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "group";
    }
};

#endif /* GROUP_H */
