#ifndef CAPTURE_H
#define CAPTURE_H

#include "op.h"


struct capture: op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "capture";
    }
};

#endif /* CAPTURE_H */
