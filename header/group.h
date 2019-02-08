#ifndef GROUP_H
#define GROUP_H

#include "op.h"


struct group: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "group";
    }
};

#endif /* GROUP_H */
