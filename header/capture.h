#ifndef CAPTURE_H
#define CAPTURE_H

#include "op.h"


struct capture: op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "capture";
    }
};

#endif /* CAPTURE_H */
