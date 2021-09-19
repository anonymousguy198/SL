//
// Created by a404m on 9/19/21.
//

#include "Lexer.h"

using namespace SL;

Lexer::Lexer(std::string str) : holder({}) {
    str += " ";
    Node node;
    for(auto it = str.begin(),end = str.end();it < end;++it){
        auto &current = *it;
        if(node.token == Node::STRING){
            if(node.str[0] == current && *(it-1) != '\\'){
                node.str += current;
                push_clear(node);
                continue;
            }
        }
        else if(isStringMarker(current)){
            push_clear_ifnempty(node);
            node.token = Node::STRING;
        }
        else if(isSpace(current)){
            push_clear_ifnempty(node);
            continue;
        }
        else if(isNumber(current) || (node.token == Node::NUMBER && current == '.')){
            if(node.token == Node::ID) {
                //goto PUSH;
            }else if(node.token != Node::NUMBER) {
                push_clear_ifnempty(node);
                node.token = Node::NUMBER;
            }
        }
        else if(isIdentifier(current)){
            if(node.token != Node::ID){
                push_clear_ifnempty(node);
                node.token = Node::ID;
            }
        }
        else if(isOperator(current)){
            if(node.token != Node::OPERATOR || !isOperator(node.str+*it)){
                if(node.str+current == "//"){
                    for(;it < end && *it != '\n';++it);
                    node.clear();
                    continue;
                }
                push_clear_ifnempty(node);
                node.token = Node::OPERATOR;
            }
        }
        else if(isBlock(current)){
            push_clear_ifnempty(node);//blocks have size = 1
            node.token = Node::BLOCK;
        }
        else if(isSymbol(current)){
            push_clear_ifnempty(node);
            node.token = Node::SYMBOL;
        }else{
            throw std::runtime_error("Lexer()");///todo
        }
        //PUSH:
        node.str += current;
    }
}

void Lexer::clear() {
    holder.clear();
}

void Lexer::push_clear(Node &node) {
    if(node.token == Node::ID) {
        if (isKeyword(node.str))
            node.token = Node::KEYWORD;
        else if (isBoolean(node.str))
            node.token = Node::BOOL;
    }
    holder.push_back(node);
    node.clear();
}

void Lexer::push_clear_ifnempty(Node &node) {
    if(!node.isEmpty()){
        push_clear(node);
    }
}