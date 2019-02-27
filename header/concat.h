#ifndef CONCAT_H
#define CONCAT_H
#include <algorithm>
#include "op.h"
using it = std::string::iterator;

struct concat : op {
    object *eval(object *o) override{
        it o_begin = o->lhs;
        o->lhs = o->rhs;
        object * basic = operands[0]->eval(o);
        if(basic) {
            it basic_begin = basic->lhs;
            basic->lhs = basic->rhs;
            object * simple = operands[1]->eval(basic);
            bool backtrack = false;
            for(;basic_begin != basic->rhs -1 && !simple; --basic->rhs, --basic->lhs) {
                backtrack = true;
                simple = operands[1]->eval(basic);
            }
            if(simple) {
                if(backtrack) {
                    simple->cap.push_back({basic_begin, basic->rhs +1});
                    std::swap(simple->cap[simple->cap.size()-1], simple->cap[simple->cap.size()-2]);
                    size_t size = 0;
                    for(it i = simple->cap[simple->cap.size()-1].lhs; i != simple->cap[simple->cap.size()-1].rhs; i++, size++);
                    simple->cap[simple->cap.size()-2].rhs -= size;
                }
                simple->lhs = o_begin;
                return simple;
            }
        }
        return nullptr;
    }
    std::string id() override {
        return "concat";
    }
};

#endif /* CONCAT_H */
