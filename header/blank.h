#ifndef BLANK_H
#define BLANK_H

#include "op.h"


struct blank : op {
    object *eval(object *o){
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "blank_space";
    }
};

#endif /* BLANK_H */