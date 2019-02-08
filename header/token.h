#include <string>

struct token {

    enum id {
        ID, ADD, ASSIGN, MULTI, END_PROGRAM
    };
    id id;
    std::string text;
};