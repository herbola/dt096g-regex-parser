#ifndef ANY_H
#define ANY_H

#include "op.h"

struct any: op {
    object *eval(object *o) override {
        std::cout<<"any: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        o->lhs++;
        if(!operands.empty()) {
            std::string id = operands[0]->id();
            if(id == "counter") {
                object * cou = operands[0]->eval(o);
                while(cou) {
                    o->lhs++;
                    cou = operands[0]->eval(o);
                }
                return o;
            } else if(id == "star") {

            }
        }
        std::cout<<operands.empty();
        int hej;
        std::cin>>hej;
        return o;
    }
    std::string id() override{
        return "any";
    }
};

#endif /* ANY_H */
