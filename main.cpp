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
    
<RE> ::= <substitute>  |  <simple-RE>
<substitute>	::=	<simple-RE>  "|" <RE>
<simple-RE>	::=  concatenation> | <basic-RE> 
<concatenation> ::= <basic-RE> <simple-RE> 
<basic-RE>	::= <star> | <plus> | <elementary-RE>
<star>	::=	<elementary-RE> "*"
<plus> ::= <elementary-RE> "+"
<elementary-RE>	::=	<char> | <group> | <any> | <counter>
<group>	::=	"(" <RE> ")"
<counter> ::= "{" <digit> "}"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<charachter>	::= <char>


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
op* regular_expression(it& first, it& last);
op* substitute_expr(it& first, it& last);
op* simple_re_expr(it& first , it& last);
op* concat_expr(it& first, it& last);
op* basic_re_expr(it& first , it& last);
op* star_expr(it& first , it& last);
op* plus_expr(it& first , it& last);
op* elemtentary_re_expr(it& first , it& last);
op* group_expr(it& first , it& last);
op* counter_expr(it& first , it& last);
op* digit_expr(it& first , it& last);
op* char_expr(it& first , it& last);
op* any_expr(it& first , it& last);

op* digit_expr(it& first, it& last) {
    std::cout<<std::endl<<"DIGIT_EXPR:"<<*first<<std::endl;
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
op* counter_expr(it& first, it& last) {
    std::cout<<std::endl<<"COUNTER_EXPR:"<<*first<<std::endl;
    it start = first;
    token tk = next_token(first, last);
    if(tk.id != token::LEFT_BRA) {
        std::cout<<"# was not a group\n";
        return nullptr;
    }
    first++;
    op* dig = digit_expr(first, last);
    if(!dig) {
        std::cout<<"? syntax error in counter\n";
        first = start;
        return nullptr;
    }
    first++;
    tk = next_token(first, last);
    if(tk.id != token::RIGHT_BRA) {
        std::cout<<"# was not a group\n";
        first = start;
        return nullptr;
    }
    first++;
    counter * expr = new counter;
    expr->operands.push_back(dig);
    return expr;
}

op* any_expr(it& first, it& last) {
    std::cout<<std::endl<<"ANY_EXPR:"<<*first<<std::endl;
    token tk = next_token(first, last);
    if(tk.id != token::ANY){
        std::cout<<"#was not any\n";
        return nullptr;
    }
    first++;
    any* expr = new any;
    return expr;
}

op* char_expr(it& first, it& last) {
    std::cout<<std::endl<<"CHAR_EXPR:"<<*first<<std::endl;
    token tk = next_token(first, last);
    if(tk.id != token::ID) {
        std::cout<<"# was not a character\n";
        return nullptr;
    }
    first++;
    character* expr = new character;
    expr->_id = tk.text;
    return expr;
}

op* group_expr(it& first, it& last) {
    std::cout<<std::endl<<"GROUP_EXPR:"<<*first<<std::endl;
    it start = first;
    token tk = next_token(first, last);
    if(tk.id != token::LEFT_PAR) {
        std::cout<<"? syntax error in group \n";
        return nullptr;
    }
    first++;
    op* re_ptr = regular_expression(first, last);
    if(!re_ptr) {
        std::cout<<"#was not group\n";
        first = start;
        return nullptr;
    }
    first++;
    tk = next_token(first, last);
    if(tk.id != tk.RIGHT_PAR) {
        first = start;
        std::cout<<"? syntax error in group \n";
        return nullptr;
    }
    first++;
    group* expr = new group;
    expr->operands.push_back(re_ptr);
    return expr;
}
op* elemtentary_re_expr(it& first, it& last) {
    it start = first;
    std::cout<<std::endl<<"ELEMENTARY_RE:"<<*first<<std::endl;
    op* char_group_any_counter = char_expr(first ,last);
    if(!char_group_any_counter) {
        char_group_any_counter = group_expr(first, last);
        if(!char_group_any_counter) {
            char_group_any_counter = any_expr(first, last);
            if(!char_group_any_counter) {
                char_group_any_counter = counter_expr(first, last);
                if(!char_group_any_counter){
                    std::cout<<"#was not elementary_re\n";
                    first = start;
                    return nullptr;
                }
            }
        }
    }
    elementary_re* expr = new elementary_re;
    expr->operands.push_back(char_group_any_counter);
    return expr;
}

op* plus_expr(it& first, it& last) {
    std::cout<<std::endl<<"PLUS_EXPR:"<<*first<<std::endl;
    it start = first;
    op* elem = elemtentary_re_expr(first, last);
    if(!elem) {
        first = start;
        return nullptr;
    }
    token tk = next_token(first, last);
    if(tk.id != token::PLUS) {
        std::cout<<"#was not plus\n";
        first = start;
        return nullptr;
    }
    plus* expr = new plus; 
    first++;
    expr->operands.push_back(elem);
    return expr;
}

op* star_expr(it& first, it& last) {
    it start = first;
    std::cout<<std::endl<<"STAR_EXPR:"<<*first<<std::endl;
    op* elem = elemtentary_re_expr(first, last);
    if(!elem) {
        first = start;
        return nullptr;
    }
    token tk = next_token(first, last);
    if(tk.id != token::STAR) {
        first = start;
        std::cout<<"#was not star\n";
        return nullptr;
    }
    first++;
    star* expr = new star; 
    expr->operands.push_back(elem);
    return expr;
}

op* basic_re_expr(it& first, it& last) {
    std::cout<<std::endl<<"BASIC_RE_EXPR:"<<*first<<std::endl;
    it start = first;
    op* star_plus_elem = star_expr(first, last);
    if(!star_plus_elem) {
        star_plus_elem = plus_expr(first, last);
        if(!star_plus_elem) {
            star_plus_elem = elemtentary_re_expr(first, last);
            if(!star_plus_elem) {
                first = start;
                return nullptr;
            }
        }
    }
    basic_re* expr = new basic_re;
    expr->operands.push_back(star_plus_elem);
    return expr;
}
op* concat_expr(it& first, it& last) {
    std::cout<<std::endl<<"CONCAT_EXPR:"<<*first<<std::endl;
    it start = first;
    op* basic_ptr = basic_re_expr(first, last);
    if(!basic_ptr) {
        first = start;
        return nullptr;
    }
    op* simple_re = simple_re_expr(first, last);
    if(!simple_re) {
        first = start;
        return nullptr;
    }
    concat* expr = new concat;
    expr->operands.push_back(basic_ptr);
    expr->operands.push_back(simple_re);
    return expr;
}

op* simple_re_expr(it& first, it& last) {
    it start = first;
    std::cout<<std::endl<<"SIMPLE_RE_EXPR:"<<*first<<std::endl;
    op* concat_or_basic = concat_expr(first, last);
    if(!concat_or_basic) {
        concat_or_basic = basic_re_expr(first, last);
        if(!concat_or_basic) {
            first = start;
            std::cout<<"# was not simple_re\n";
            return nullptr;
        }
    }
    simple_re* expr = new simple_re;
    expr->operands.push_back(concat_or_basic);
    return expr;
}

op* substitute_expr(it &first, it &last) { // <substitute> ::= <simple-RE>  "|" <RE>
    std::cout<<std::endl<<"substitute_expr:"<<*first<<std::endl;
    it start = first;
    op* simple_ptr = simple_re_expr(first, last);
    if(!simple_ptr) {
        first = start;
        return nullptr;
    }
    op* re_ptr = regular_expression(first ,last);
    if(!re_ptr) {
        first = start;
        return nullptr;
    }
    substitute* expr = new substitute;
    expr->operands.push_back(simple_ptr);
    expr->operands.push_back(re_ptr);
    return expr;
}

op* regular_expression(it &first, it &last) { // <RE> ::= <substitute>  |  <simple-RE>
    std::cout<<std::endl<<"REGULAR_EXPR:"<<*first<<std::endl;
    if(*first == *last) {
        return nullptr;
    }
    token tk = next_token(first, last);
    op* sub_or_simple = substitute_expr(first, last);
    if(!sub_or_simple) {
        sub_or_simple = simple_re_expr(first, last);
    }   
    re* expr = new re;
    expr->operands.push_back(sub_or_simple);
    return expr;
}

void loop(op*& o){
    std::cout<<o->id()<<std::endl;
    for(auto e : o->operands) {
        loop(e);
    }
}
int main(int argc, char** argv) {
    std::string source = "Waterloo I  was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    std::string input = "odwoddwadawdawdawdawdwadwado.{3}";
    //std::string input = "loda";   
    //std::string input = "(.|.)";
    it begin = input.begin();
    it end = input.end();
    op* result = regular_expression(begin, end);
    std::cout<<std::endl;
    loop(result);
    int stop;
    std::cin>>stop;
    return 0;
}


