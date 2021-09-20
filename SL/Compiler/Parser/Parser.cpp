//
// Created by a404m on 9/19/21.
//

#include "Parser.h"

using namespace SL;

Parser::Parser(Lexer lexer) {
    /*{
        auto &lexed = lexer.holder;
        std::vector<Node> line{};

        for (auto it = lexed.begin(), end = lexed.end(); it < end; ++it) {
            if (it->token == Node::SYMBOL) {
                if (it->str == ";") {
                    this->primaryHolder.push_back(line);
                    line.clear();
                    continue;
                }
            }
            line.push_back(*it);
        }
        lexer.clear();
        if (!line.empty())
            throw std::runtime_error("Parser::Parser");
    }*/

    for(auto& line : lexer.holder) {
        parseLine(line);
        holder.push_back(line[0]);
    }
    lexer.clear();
}

void Parser::parseLine(std::vector<Node>& line) {
    auto orderIt = orders.begin();

    for (auto it = line.end(),begin = line.begin(),end = it;line.size() > 1;end = line.end(),it = end){
        for(auto temp = begin;temp < end;++temp){
            if(temp->operands.empty()) {
                setOperatorKind(begin, end, temp);
                auto founded = isInBy_string_token(*orderIt, temp);
                if (founded != orderIt->cend()) {
                    if (*founded == *temp) {
                        it = temp;
                        if(it->token == Node::OPERATOR && it->str == "="){//left associative
                            continue;
                        }else{
                            break;
                        }
                    } else {
                        temp->specialToken = Node::INVALID;
                    }
                }
            }
        }
        if(it == end){
            ++orderIt;
            if(orderIt == orders.end()){
                throw std::runtime_error("Parser::parseLine");
            }
            continue;
        }
        switch (it->token) {
            case Node::BLOCK: {
                std::string close;

                int in = 0;
                std::vector<Node> tempLine;
                while(true) {
                    if(it->token == Node::BLOCK){
                        if(it->str == "(")
                            ++in;
                        else if(it->str == ")")
                            --in;
                        else
                            throw std::runtime_error("Parser::parseLine");

                        if(!in){
                            tempLine.push_back(*it);
                            tempLine.erase(tempLine.begin());
                            tempLine.erase(tempLine.end()-1);
                            parseLine(tempLine);
                            *it = tempLine[0];
                            break;
                        }
                    }
                    if(it >= line.end()){
                        throw std::runtime_error("Parser::parseLine");
                    }
                    tempLine.push_back(*it);
                    line.erase(it);
                }
            }
                break;
            case Node::OPERATOR:
                switch (it->specialToken) {
                    case Node::OP_LEFT:
                        it->operands.push_back(*(it-1));
                        line.erase(it-1);
                        --it;//standard 23.1.2
                        break;
                    case Node::OP_RIGHT:
                        it->operands.push_back(*(it+1));
                        line.erase(it+1);
                        //no need to change it | standard 23.1.2
                        break;
                    case Node::OP_BOTH:
                        it->operands.push_back(*(it-1));
                        it->operands.push_back(*(it+1));
                        line.erase(it+1);
                        line.erase(it-1);
                        --it;//standard 23.1.2
                        break;
                    default:
                        throw std::runtime_error("Parser::parseLine");
                }
                break;
            case Node::KEYWORD:{
                if(it->str == "print"){
                    it->operands.push_back(*(it+1));
                    line.erase(it+1);
                }
            }
                break;
            default:
                throw std::runtime_error("Parser::parseLine");
        }
    }
}

void Parser::setOperatorKind(const std::vector<Node>::iterator &begin,const std::vector<Node>::iterator &end,const std::vector<Node>::iterator &it) {
    if(it->token == Node::BLOCK){
        it->specialToken = Node::OP_BETWEEN;
    }else if(it == begin || !isOperand(*(it-1))){
        if(it == end || !isOperand(*(it+1))){
            return;
        }else{
            it->specialToken = Node::OP_RIGHT;
        }
    }else if(it == end || !isOperand(*(it+1))){
        it->specialToken = Node::OP_LEFT;
    }else{
        it->specialToken = Node::OP_BOTH;
    }
}

bool Parser::isOperand(const Node &node) {
    switch (node.token) {
        case Node::STRING:
        case Node::NUMBER:
        case Node::BOOL:
        case Node::ID:
            return true;
        case Node::BLOCK:
        case Node::OPERATOR:
            return !node.operands.empty();
        default:
            return false;
    }
}

std::vector<Node>::const_iterator Parser::isInBy_string_token(const std::vector<Node> &vec, const std::vector<Node>::const_iterator &it) {
    for(auto temp = vec.cbegin(), end = vec.cend();temp < end;++temp)
        if(temp->str == it->str && temp->token == it->token)
            return temp;

    return vec.cend();
}