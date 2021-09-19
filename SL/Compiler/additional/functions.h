//
// Created by a404m on 9/19/21.
//

#ifndef SL_FUNCTIONS_H
#define SL_FUNCTIONS_H

#include <iostream>
#include <string>

namespace SL {
    extern bool isSpace(char);
    extern bool isStringMarker(char);
    extern bool isNumber(char);
    extern bool isBlock(char);
    extern bool isIdentifier(char);//ID
    extern bool isKeyword(const std::string &);
    extern bool isBoolean(const std::string &);
    extern bool isSymbol(char);
    extern bool isOperator(char);
    extern bool isOperator(const std::string &);
}//namespace SL

#endif //SL_FUNCTIONS_H
