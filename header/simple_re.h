#ifndef SIMPLE_RE_H
#define SIMPLE_RE_H

#include "op.h"
#include "object.h"

struct simple_re : op {
    object *eval(object *o) override{
        std::cout<<"simple"<<std::endl<<*(o->lhs)<<std::endl;
        return operands[0]->eval(o);
    }
    std::string id() override{
        return "simple_re";
    }
};

#endif /* SIMPLE_RE_H */