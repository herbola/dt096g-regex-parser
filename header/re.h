#ifndef RE_H
#define RE_H

#include "op.h"
#include "object.h"

struct re : op {
    object *eval(object *o) override{
        while(o->rhs != o->end) {
            std::cout<<"re: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
            object * sub_sim = operands[0]->eval(o);
            if(sub_sim) {
                return sub_sim;
            }
            o->lhs = ++o->rhs;
            std::cout<<std::endl;
        }
        return nullptr;
    }
    std::string id() override{
        return "re";
    }
};

#endif /* RE_H */
