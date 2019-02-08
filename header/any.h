#ifndef ANY_H
#define ANY_H

#include "op.h"


struct any: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
