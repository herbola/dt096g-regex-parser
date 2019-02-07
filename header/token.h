

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <algorithm>
#include <vector>
#include <cctype>


struct token {
    enum id {
        ID, ASSIGN, ADD, MULT, END_PROGRAM
    };
    id id;
    std::string text;
};

using it = std::string::iterator;

token next_token(it& first, it last) {
    // remove whitespace
    while (std::isspace(*first)) {
        first++;
    }

    if (first == last) {
        return token{ token::END_PROGRAM, ""};
    }

    token tk;
    switch (*first) {
        case '=':
            tk = {token::ASSIGN, "="};
            break;
        case '+':
            tk = {token::ADD, "+"};
            break;
        case '*':
            tk = {token::MULT, "*"};
            break;
        default:
            tk = {token::ID, std::string(first, first + 1)};
    };
    return tk;
}

#endif /* TOKEN_H */

