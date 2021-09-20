//
// Created by a404m on 9/19/21.
//

#ifndef SL_NODE_H
#define SL_NODE_H


#include "../additional/functions.h"
#include "../additional/types.h"
#include <vector>

namespace SL {
    struct Node {
    public:
        enum Token {
            NONE = 0,
            STRING,
            NUMBER,
            BOOL,
            BLOCK,//{} () ...
            OPERATOR,
            KEYWORD,
            ID,
            SYMBOL
        };
        enum SpecialToken{
            INVALID = 0,
            OP_LEFT,//i.e. a++
            OP_RIGHT,//i.e. +a
            OP_BOTH,//i.e. a+2
            OP_BETWEEN//i.e. (a+2)
        };
        std::string str;
        Token token;
        SpecialToken specialToken;
        std::vector<Node> operands;

        explicit Node(std::string  = "", Token = NONE, SpecialToken = INVALID, std::initializer_list<Node> = {});

        void clear();

        bool isEmpty() const;

        //used for std::map
        bool operator==(const Node&) const;
        bool operator!=(const Node&) const;
        bool operator>(const Node&) const;
        bool operator<(const Node&) const;
        bool operator>=(const Node&) const;
        bool operator<=(const Node&) const;
    };
}//namespace SL



#endif //SL_NODE_H
