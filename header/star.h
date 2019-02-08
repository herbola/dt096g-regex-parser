#ifndef STAR_H
#define STAR_H

#include "star.h"


struct star : op {
    char eval(){
        return operands[0]->eval();
    }
    std::string id() override{
        return "star";
    }
};

#endif /* STAR_H */