#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"
#include <string>

struct character : op {
    std::string _id;
    object *eval(object *o) override{
        std::cout<<"charater"<<std::endl<<*(o->lhs)<<std::endl;
        for (int i = 0; i < size(); i++) {
            std::cout<<*(o->lhs+i)<<i;
            if(*(o->lhs+i) != *(id().begin()+i)) {
                return nullptr;
            }
        }
        o->rhs += size()-1;
        return o;
    }
    std::string id() override{
        return this->_id;
    }
    int size() {
        return _id.size();
    }
};

#endif /* CHARACTER_H */