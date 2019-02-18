#ifndef STAR_H
#define STAR_H

#include "star.h"


struct star : op {
    std::string eval(std::string source){
        return operands[0]->eval("");
    }
    std::string id() override{
        return "star";
    }
};

#endif /* STAR_H */