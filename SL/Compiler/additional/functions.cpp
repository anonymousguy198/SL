//
// Created by a404m on 9/19/21.
//


#include "functions.h"
namespace SL{
    extern bool isSpace(char c){
        return isspace(c);
    }
    extern bool isStringMarker(char c){
        return c == '\"' || c == '\'';
    }
    extern bool isNumber(char c){
        return c >= '0' && c <= '9';
    }
    extern bool isBlock(char c){
        return c == '{' || c == '}' || c == '(' || c == ')';
    }
    extern bool isIdentifier(char c){
        return isalpha(c);
    }
    extern bool isKeyword(const std::string &str){
        static std::string keywords[] = {"print"};
        for(const auto &item : keywords)
            if(str == item)
                return true;

        return false;
    }
    extern bool isBoolean(const std::string &str){
        return str == "true" || str == "false";
    }
    extern bool isSymbol(char c){
        return c == ';';
    }
    extern bool isOperator(char c){
        return c == '+' || c == '-' || c == '/' || c == '*' || c == '=' || c == '!' || c == '>' || c == '<';
    }
    extern bool isOperator(const std::string &str){
        static std::string operators[] = {"+","-","/","*","=","==","!=",">","<",">=","<="};
        for(const auto &item : operators)
            if(str == item)
                return true;

        return false;
    }
}//namespace SL