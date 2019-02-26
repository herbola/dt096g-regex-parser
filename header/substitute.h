#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"
#include "object.h"


struct substitute : op {
    object *eval(object *o){
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "substitute";
    }
};

#endif /* SUBSTITUTE_H */