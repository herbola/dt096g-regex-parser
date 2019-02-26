#ifndef CONCAT_H
#define CONCAT_H

#include "op.h"
using it = std::string::iterator;

struct concat : op {
    object *eval(object *o) override{
        std::cout<<"concat: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        object * basic = operands[0]->eval(o);
        if(basic) {
            print(id(),basic);
            std::cout<<"TEST: "<<"LHS:"<<*(basic->lhs)<<" RHS:"<<*(basic->rhs)<<std::endl;
            basic->rhs++;
            std::cout<<"TEST: "<<"LHS:"<<*(basic->lhs)<<" RHS:"<<*(basic->rhs)<<std::endl;
            object * simple = operands[1]->eval(basic);
            if(simple) {
                
                return simple;
            } 
        }
        return nullptr;
    }
    std::string id() override{
        return "concat";
    }
};

#endif /* CONCAT_H */
