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
    
<RE>	::=	 <substitute> | <simple-RE>  if sub + 3 exexex
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=	<basic-RE> |  concatenation> 
<concatenation>	::=	<basic-RE> <simple-RE> 
<basic-RE>	::=	 <elementary-RE> | <plus> | <star> 
<star>	::=	<elementary-RE> "*" ändra sida?
<plus>	::=	<elementary-RE> "+"  ändra sida?
<elementary-RE>	::=	<char> | <group> | <any> | <counter>
<group>	::=	"(" <RE> ")" , "(" <RE> ")" <RE>
<counter> ::= "{" <digit> "}"
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

op* regular_expression(it first, it last);
op* substitute_expr(it first, it last);
op* simple_re_expr(it first , it last);
op* concat_expr(it first , it last);
op* basic_re_expr(it first , it last);
op* star_expr(it first , it last);
op* plus_expr(it first , it last);
op* elemtentary_re_expr(it first , it last);
op* group_expr(it first , it last);
op* counter_expr(it first , it last);
op* digit_expr(it first , it last);
op* char_expr(it first , it last);
op* any_expr(it first , it last);

op* char_expr(it first, it last) { // <charachter>	::=	any non metacharacter | "\" metacharacter
    character* chr = new character;
    token tk = next_token(first, last);
    if(tk.id != token::ID) {
        std::cout<<"was not a character\n";
        return nullptr;
    }
    chr->_id = tk.text;
    first++;
    op* re_expr = regular_expression(first, last);
    if(re_expr) {
        chr->operands.push_back(re_expr);
    }
    return chr;
}

op* digit_expr(it first, it last) { // <digit> ::= [0 - 9]
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

    return nullptr;
}

op* any_expr(it first, it last) {
    token tk = next_token(first, last);
    if(tk.id != token::ANY) {
        return nullptr;
    }
    return new any;
}
op* counter_expr(it first , it last) { // <counter> ::= "{" <digit> "}"
    token left_bra = next_token(first, last);
    counter* expr = new counter;
    if(left_bra.id != token::LEFT_BRA) {
        std::cout<<"was not counter\n";
        return nullptr;
    }
    first++;
    op* dig = digit_expr(first, last);
    if(!dig) {
        std::cout<<"Syntax error in counter_expr\n";
        return nullptr;
    }
    first++;
    token right_bra = next_token(first, last);
    if(right_bra.id != token::RIGHT_BRA) {
        std::cout<<"Syntax error in counter_expr, token::RIGHT_BRA\n";
        return nullptr;
    }
    first++;
    expr->operands.push_back(dig);
    return expr;
}
op* group_expr(it first , it last) { // <group>	::=	"(" <RE> ")"
    token left_par = next_token(first, last);
    group* expr = new group;
    if(left_par.id != token::LEFT_PAR) {
        std::cout<<"was not group\n";
        return nullptr;
    }
    first++;
    op* re = regular_expression(first, last);
    if(!re) {
        std::cout<<"Syntax error in group_expr\n";
        return nullptr;
    }
    first++;
    token right_par = next_token(first, last);
    if(right_par.id != token::RIGHT_PAR) {
        std::cout<<"Syntax error in group_expr, token::RIGHT_PAR\n";
        return nullptr;
    }
    first++;
    expr->operands.push_back(re);
    return expr;
}
op* star_expr(it first, it last) { // <star> ::= <elementary-RE> "*" ändra sida?
    op* elementary_re_expr = elemtentary_re_expr(first, last);
    if(!elementary_re_expr) {
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::STAR) {
        std::cout<<"was not star\n";
        return nullptr;
    }
    star * expr = new star;
    expr->operands.push_back(elementary_re_expr);
    first++;
    return expr;
}

op* plus_expr(it first, it last) { // <plus> ::= <elementary-RE> "+"
    op* elementary_re_expr = elemtentary_re_expr(first, last);
    if(!elementary_re_expr) {
        return nullptr;
    }
    first++;
    token tk = next_token(first, last);
    if(tk.id != token::PLUS) {
        std::cout<<"was not plus\n";
        return nullptr;
    }
    plus* expr = new plus;
    expr->operands.push_back(elementary_re_expr);
    first++;
    return expr;
}
op* elemtentary_re_expr(it first , it last) { // <elementary-RE>	::=	<char> | <group> | <any> | <counter>
    op* char_group_any_counter = char_expr(first, last);
    if(!char_group_any_counter) {
        char_group_any_counter = group_expr(first, last);
        if(!char_group_any_counter) {
            char_group_any_counter = any_expr(first, last);
            if(!char_group_any_counter) {
                char_group_any_counter = counter_expr(first, last);
                if(char_group_any_counter) {
                    first = first + 3;
                }
            } 
        }
    }
    if(!char_group_any_counter) {
        std::cout<<"was not elementary re\n";
        return nullptr;
    }
    elementary_re * expr = new elementary_re;
    expr->operands.push_back(char_group_any_counter);
    return expr;
}
op* concat_expr(it first , it last) { // <concatenation> ::= <basic-RE> <simple-RE> 

    op* basic_expr = basic_re_expr(first, last);
    if(!basic_re_expr) {
        std::cout<<"was not concat\n";
        return nullptr;
    }
    first++;
    op* simple_expr = new simple_re;
    simple_expr = simple_re_expr(first, last);
    if(!simple_re_expr) {
        std::cout<<"was not concat\n";
        return nullptr;
    }
    concat* expr = new concat;
    expr->operands.push_back(basic_expr);
    expr->operands.push_back(simple_expr);
    return expr;
}
op* basic_re_expr(it first , it last) { // <basic-RE> ::= <elementary-RE> | <plus> | <star> 
    op* elem_or_star_or_plus = elemtentary_re_expr(first, last);
    if(!elem_or_star_or_plus) {
        elem_or_star_or_plus = star_expr(first, last);
        if(!elem_or_star_or_plus) {
          elem_or_star_or_plus = plus_expr(first, last);
          if(elem_or_star_or_plus) {
              first = first + 2;
          }
        } else {
            first = first + 2;
        }
    }
    if(!elem_or_star_or_plus) {
       std::cout<<"was not basic re \n";
       return nullptr;
    }
    basic_re* expr = new basic_re;
    expr->operands.push_back(elem_or_star_or_plus);
    return expr;
}
op* simple_re_expr(it first , it last) { // <simple-RE>	::=	<basic-RE> |  concatenation>
    op* basic_re_or_concat = basic_re_expr(first, last);
    if(!basic_re_or_concat) {
        basic_re_or_concat = concat_expr(first, last);
    }
    if(!basic_re_or_concat) {
        std::cout<<"Syntax error in simple_re_expr\n";
        return nullptr;
    }
    simple_re* expr = new simple_re;
    expr->operands.push_back(basic_re_or_concat);
    return expr;
}

op* substitute_expr(it first, it last) { // <substitute> ::= <simple-RE>  "|" <RE>
    substitute* expr = new substitute;
    op* simple_expr = simple_re_expr(first, last); //lhs
    if(!simple_expr) {
        return nullptr;
    } 
    first++;
    token or_token = next_token(first, last);
    if(or_token.id = token::OR) {
        std::cout<<"was not substitute \n";
        return nullptr;
    }
    first++;
    op* re_expr = new re;
    re_expr = regular_expression(first, last);
    if(!regular_expression) {
        return nullptr;
    }
    expr->operands.push_back(simple_expr);
    expr->operands.push_back(re_expr);
    return expr;
}

op* regular_expression(it first, it last) { // <RE> ::= <substitute>  |  <simple-RE>
    op* expr = new re;
    op* simple_or_substitue= substitute_expr(first, last);
    if (!simple_or_substitue) {
        simple_or_substitue= simple_re_expr(first, last);
    }
    if(!simple_or_substitue) {
        return nullptr;
    }
    expr->operands.push_back(simple_or_substitue);
    return expr;
}

void loop(op*& o){
    std::cout<<o->id()<<std::endl;
    for(auto e : o->operands) {
        loop(e);
    }
}
int main(int argc, char** argv) {
    std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "lo* could.{3}";
    //std::string input = "(.|.)";
    op* result = regular_expression(input.begin(), input.end());
    std::cout<<std::endl;
    loop(result);
    int stop;
    std::cin>>stop;
    return 0;
}


