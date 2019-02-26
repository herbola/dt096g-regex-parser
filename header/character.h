#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"
#include <string>

struct character : op {
    std::string _id;
    object *eval(object *o) override{
        std::cout<<"character: "<<"LHS:"<<*(o->lhs)<<" RHS:"<<*(o->rhs)<<std::endl;
        for (int i = 0; i < size(); i++) {
            if(*(o->rhs+i) != *(_id.begin()+i)) {
                return nullptr;
            }
        }
        std::cout<<"SUCCED";
        o->rhs += size();
        return o;
    }
    std::string id() override{
        return "character(" + this->_id + ")";
    }
    int size() {
        return _id.size();
    }
};

#endif /* CHARACTER_H */