#include <cstdlib>
#include <iostream>
#include <string>
#include "header/op.h"
#include "header/token.h"
#include "header/re.h"
#include "header/simple_re.h"
#include "header/substitute.h"
#include "header/basic_re.h"
#include "header/concat.h"
#include "header/elementary_re.h"
#include "header/plus.h"
#include "header/group.h"
#include "header/star.h"
#include "header/character.h"
#include "header/digit.h"
#include "header/counter.h"
#include "header/any.h"


/*
    
<RE>	::=	<simple-RE> | <substitute> 
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=	<basic-RE> |  concatenation> 
<concatenation>	::=	<basic-RE> <simple-RE> 
<basic-RE>	::=	 <elementary-RE> | <plus> | <star> 
<star>	::=	<elementary-RE> "*" ändra sida?
<plus>	::=	<elementary-RE> "+"  ändra sida?
<elementary-RE>	::=	<char> | <group> | <any> | <counter>
<group>	::=	"(" <RE> ")"
<count> ::= "{" <digit> "}"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<charachter>	::=	any non metacharacter | "\" metacharacter , <char> <RE>

*/


/*
+ eller, passar ett av två alternativ. Syntax: OP1+OP2
* flera, passar ett eller flera upprepningar av en operand. Syntax: OP*
() infångningsgrupp, deluttryck. Uttrycket parsas separat. Syntax: (EXPR)
. tecken. matchar varlfritt tecken. Syntax: .
{} räknare. matchar precis N stycken operander. Syntax: OP{3}
\I ignorera versalisering. Syntax EXPR\I
\O{} vilken infångningsgrupp som ska ges som output. Syntax: EXPR\O{2}. Default \O{0} hela matchningen.
*/
using it = std::string::iterator;

op* _re(it first, it last);
op* _substitute(it first, it last);
op* _simple_re(it first , it last);
op* _concat(it first , it last);
op* _basic_re(it first , it last);
op* _star(it first , it last);
op* _plus(it first , it last);
op* _elementary_re(it first , it last);
op* _group(it first , it last);
op* _counter(it first , it last);
op* _digit(it first , it last);
op* _character(it first , it last);
op* _any(it first , it last);

op* _character(it first, it last) { // <charachter>	::=	any non metacharacter | "\" metacharacter
    character* chr = new character;
    token tk = next_token(first, last);
    if(tk.id != token::ID) {
        std::cout<<"Syntax error in _character\n";
        return nullptr;
    }
    chr->_id = tk.text;
    std::cout<<"\nHEWAHEAWHEHWEH"<<chr->id()<<"\n";
    return chr;
}

op* _digit(it first, it last) { // <digit> ::= [0 - 9]
    digit* dig = new digit;
    token tk = next_token(first, last);
    if(tk.id != token::ID) {
        return nullptr;
    }
    for(auto e : dig->digits) {
        if(e == tk.text[0]) {
            dig->_id = tk.text;
            return dig;
        }
    }
    std::cout<<"Syntax error in _digit\n";
    return nullptr;
}

op* _any(it first, it last) {
    token tk = next_token(first, last);
    if(tk.id != token::ANY) {
        return nullptr;
    }
    return new any;
}
op* _counter(it first , it last) {
    token left_bra = next_token(first, last);
    counter* expr = new counter;
    if(left_bra.id != token::LEFT_BRA) {
        std::cout<<"Syntax error in _counter, token::LEFT_BRA\n";
        return nullptr;
    }
    first++;
    op* dig = _digit(first, last);
    if(!dig) {
        std::cout<<"Syntax error in _counter\n";
        return nullptr;
    }
    first++;
    token right_bra = next_token(first, last);
    if(right_bra.id != token::RIGHT_BRA) {
        std::cout<<"Syntax error in _counter, token::RIGHT_BRA\n";
        return nullptr;
    }
    first++;
    expr->operands.push_back(dig);
    return expr;
}
op* _group(it first , it last) { // <group>	::=	"(" <RE> ")"
    token left_par = next_token(first, last);
    group* expr = new group;
    if(left_par.id != token::LEFT_PAR) {
        std::cout<<"Syntax error in _group, token::LEFT_PAR\n";
        return nullptr;
    }
    first++;
    op* re = _re(first, last);
    if(!re) {
        std::cout<<"Syntax error in _group\n";
        return nullptr;
    }
    first++;
    token right_par = next_token(first, last);
    if(right_par.id != token::RIGHT_PAR) {
        std::cout<<"Syntax error in _group, token::RIGHT_PAR\n";
        return nullptr;
    }
    first++;
    expr->operands.push_back(re);
    return expr;
}
op* _star(it first, it last) { // <star> ::= <elementary-RE> "*" ändra sida?
    op* elementary_re_expr = _elementary_re(first, last);
    if(!elementary_re_expr) {
        std::cout<<"Syntax error in _star, elementary_re_expr\n";
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::STAR) {
        std::cout<<"Syntax error in _star, token::STAR\n";
        return nullptr;
    }
    star * expr = new star;
    expr->operands.push_back(elementary_re_expr);
    first++;
    return expr;
}

op* _plus(it first, it last) { // <plus> ::= <elementary-RE> "+"
    op* elementary_re_expr = _elementary_re(first, last);
    if(!elementary_re_expr) {
        std::cout<<"Syntax error in _plus, elementary_re_expr\n";
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::PLUS) {
        std::cout<<"Syntax error in _plus, token::PLUS\n";
        return nullptr;
    }
    plus* expr = new plus;
    expr->operands.push_back(elementary_re_expr);
    first++;
    return expr;
}
op* _elementary_re(it first , it last) { // <elementary-RE>	::=	<char> | <group> | <any> | <counter>
    op* char_group_any_counter = _character(first, first);
    if(!char_group_any_counter) {
        char_group_any_counter = _group(first, last);
        if(!char_group_any_counter) {
            char_group_any_counter = _any(first, last);
            if(!char_group_any_counter) {
                char_group_any_counter = _counter(first, last);
            }
        }
    }
    if(!char_group_any_counter) {
        std::cout<<"Syntax error in _elementary_re\n";
        return nullptr;
    }
    elementary_re * expr = new elementary_re;
    expr->operands.push_back(char_group_any_counter);
    return expr;
}
op* _concat(it first , it last) { // <concatenation> ::= <basic-RE> <simple-RE> 

    op* basic_re_expr = _basic_re(first, last);
    if(!basic_re_expr) {
        std::cout<<"Syntax error in _concat, basic_re\n";
        return nullptr;
    }
    first++;
    op* simple_re_expr = new simple_re;
    simple_re_expr = _simple_re(first, last);
    if(!simple_re_expr) {
        std::cout<<"Syntax error in _concat, simple_re\n";
        return nullptr;
    }
    concat* expr = new concat;
    expr->operands.push_back(basic_re_expr);
    expr->operands.push_back(simple_re_expr);
    return expr;
}
op* _basic_re(it first , it last) { // <basic-RE> ::= <elementary-RE> | <plus> | <star> 
    op* elem_or_star_or_plus = _elementary_re(first, last);
    if(!elem_or_star_or_plus) {
        elem_or_star_or_plus = _star(first, last);
        if(!elem_or_star_or_plus) {
          elem_or_star_or_plus = _plus(first, last);  
        }
    }
    if(!elem_or_star_or_plus) {
       std::cout<<"Syntax error in _basic_re\n"; 
       return nullptr;
    }
    basic_re* expr = new basic_re;
    expr->operands.push_back(elem_or_star_or_plus);
    return expr;
}
op* _simple_re(it first , it last) { // <simple-RE>	::=	<basic-RE> |  concatenation> 
    op* basic_re_or_concat = _basic_re(first, last);
    if(!basic_re_or_concat) {
        basic_re_or_concat = _concat(first, last);
    }
    if(!basic_re_or_concat) {
        std::cout<<"Syntax error in _simple_re\n";
        return nullptr;
    }
    simple_re* expr = new simple_re;
    expr->operands.push_back(basic_re_or_concat);
    return expr;
}

op* _substitute(it first, it last) { // <substitute> ::= <simple-RE>  "|" <RE>
    substitute* expr = new substitute;
    op* simple_re_expr = _simple_re(first, last); //lhs
    if(!simple_re_expr) {
        std::cout<<"Syntax error in substitute, SIMPLE_RE\n";
        return nullptr;
    } 
    first++;
    token or_token = next_token(first, last);
    if(or_token.id = token::OR) {
        std::cout<<"Syntax error in substitute, OR \n";
        return nullptr;
    }
    first++;
    op* re_expr = new re;
    re_expr = _re(first, last);
    if(!re_expr) {
        std::cout<<"Syntax error in substitute, RE\n";
        return nullptr;
    }
    expr->operands.push_back(simple_re_expr);
    expr->operands.push_back(re_expr);
    return expr;
}

op* _re(it first, it last) { // <RE> ::= <simple-RE> | <substitute> 
    op* expr = new re;
    op* simple_or_substitue= _simple_re(first, last);
    if (!simple_or_substitue) {
        simple_or_substitue= _substitute(first, last);
    }
    if(!simple_or_substitue) {
        return nullptr;
    }
    expr->operands.push_back(simple_or_substitue);

    return expr;
}

int main(int argc, char** argv) {
    std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "lo* could.{3}";
    op* result = _re(input.begin(), input.end());
    int stop;
    std::cin>>stop;
    return 0;
}


