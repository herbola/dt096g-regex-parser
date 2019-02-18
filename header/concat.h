#ifndef CONCAT_H
#define CONCAT_H

#include "op.h"


struct concat : op {
    std::string eval(std::string source){
        return operands[0]->eval(source) + operands[1]->eval(source);
    }
    std::string id() override{
        return "concat";
    }
};

#endif /* CONCAT_H */
