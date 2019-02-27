#ifndef CHARACTER_H
#define CHARACTER_H

#include "op.h"
#include <string>

struct character : op {
    std::string _id;
    object *eval(object *o) override {
        if(o->lower) std::transform(_id.begin(), _id.end(), _id.begin(), ::tolower);
        for (int i = 0; i < size(); i++) {
            if(*(o->rhs+i) != *(_id.begin()+i)) {
                return nullptr;
            }
        }
        o->rhs += size();
        o->cap.push_back({o->rhs - size(), o->rhs});
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