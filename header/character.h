#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"
#include <string>

struct character : op {
    std::string _id;
    object *eval(object *o){
        for (int i = 0; i< _id.size(); i++) {
            if(*(o->lhs+i) != *(id().begin()+i)) {
                return nullptr;
            }
        }
        o->rhs += this->id().size();
        return o;
    }
    std::string id() override{
        return this->_id;
    }
};

#endif /* CHARACTER_H */