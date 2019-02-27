#ifndef RE_H
#define RE_H

#include "op.h"
#include "object.h"

struct re : op {
    object *eval(object *o) override{
        o = operands[0]->eval(o);
        if(o) {
            if(o->captured > 0) {
                if(o->captured < o->cap.size()) {
                    o->lhs = o->cap[o->captured].lhs;
                     o->rhs = o->cap[o->captured].rhs;
                } else return nullptr; // capture failed
            }
        }
        return o;
    }
    std::string id() override{
        return "re";
    }
};

#endif /* RE_H */
