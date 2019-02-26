#ifndef ELEMENTARY_RE_H
#define ELEMENTARY_RE_H

#include "op.h"
#include "object.h"
#include <iostream>

struct elementary_re: op {
    object *eval(object *o) override{
        std::cout<<"elem"<<std::endl<<*(o->lhs)<<std::endl;
        std::string prev = operands[0]->id();
        object* elem = operands[0]->eval(o);
        while(!elem) {
            o->rhs =++o->lhs;
            elem = operands[0]->eval(o);
        }
        if(prev == "char") {
            return elem;
        } else if(prev == "group") {
            
        } else if(prev == "any") {
            
        }
        return elem;
    }
    std::string id() override{
        return "elementary_re";
    }
};

#endif /* ELEMENTARY_RE_H */
