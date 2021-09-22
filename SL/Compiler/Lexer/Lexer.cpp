//
// Created by a404m on 9/19/21.
//

#include "Lexer.h"

using namespace SL;

Lexer::Lexer(std::string str) : holder({}),primaryHolder({}) {
    str += " ";
    Node node;
    for(auto it = str.begin(),end = str.end();it < end;++it){
        auto &current = *it;
        if(node.token == Node::STRING){
            if(current == '\\'){
                ++it;
                switch (*it) {
                    case 'n':
                        node.str += '\n';
                        break;
                    case 't':
                        node.str += '\t';
                        break;
                    case 'v':
                        node.str += '\v';
                        break;
                    case 'b':
                        node.str += '\b';
                        break;
                    case 'r':
                        node.str += '\r';
                        break;
                    case 'a':
                        node.str += '\a';
                        break;
                    case '\\':
                        node.str += '\\';
                        break;
                    case '\"':
                        node.str += '\"';
                        break;
                    case '\'':
                        node.str += '\'';
                        break;
                    default:
                        throw std::runtime_error(std::string("Unknown char \\") + *it);
                }
                continue;
            }else if(node.str[0] == current){
                node.str.erase(0,1);
                push_clear(node);
                continue;
            }
        }
        else if(isStringMarker(current)){
            push_clear_ifnempty(node);
            node.token = Node::STRING;
        }else if(current == '\n'){
            push_clear_ifnempty(node);
            node.token = Node::SYMBOL;
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
    int in = 0;
    std::vector<Node> line;
    for(auto it = primaryHolder.begin(),begin = it,end = primaryHolder.end();it < end;++it){
        if(it->token == Node::SYMBOL){
            if(it->str == "\n"){
                if(it == begin || in || ((it+1)->token == Node::SYMBOL && (it+1)->str == "\n") || (it+1)->isEqualByTokenAndString(Node::OP_COMMA) || (line.end()-1)->isEqualByTokenAndString(Node::OP_COMMA)){
                    continue;
                }else{
                    if (!line.empty()) {
                        holder.push_back(line);
                        line.clear();
                    }
                }
            }else{
                if (it->str == ";") {
                    if (!line.empty()) {
                        holder.push_back(line);
                        line.clear();
                    }
                }
            }
        }else{
            line.push_back(*it);
            if (it->token == Node::BLOCK) {
                if (it->str == "(")
                    ++in;
                else if (it->str == ")")
                    --in;
            }
        }
    }
    primaryHolder.clear();
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
    primaryHolder.push_back(node);
    node.clear();
}

void Lexer::push_clear_ifnempty(Node &node) {
    if(!node.isEmpty()){
        push_clear(node);
    }
}