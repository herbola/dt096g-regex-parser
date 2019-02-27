#ifndef STAR_H
#define STAR_H

#include "star.h"
#include "object.h"

struct star : op {
    object *eval(object *o) override{
        // quick fix .*
        if(!operands.empty()) {
            if(operands[0]->id() == "elementary_re") {
                if(!operands[0]->operands.empty()) {
                    if(operands[0]->operands[0]->id() =="any"){    
                        o->rhs = o->end;
                        return o;
                    }
                }
            }
        }
        object* elem = operands[0]->eval(o);
        if(elem) {
            char chr = *elem->rhs;
            while(*(elem->rhs) == chr) {
                elem->rhs++;
            }
        } 
        return elem;
    }
    std::string id() override{
        return "star";
    }
};

#endif /* STAR_H */