#ifndef PLUS_H
#define PLUS_H

#include "op.h"


struct plus : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "plus";
    }
};

#endif /* PLUS_H */