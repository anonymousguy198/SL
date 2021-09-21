//
// Created by a404m on 9/19/21.
//

#include "CodeGenerator.h"

using namespace SL;

CodeGenerator::CodeGenerator(Parser parser) : holder({}), lastHelper(0){
    for(auto& node : parser.holder){
        generateByteCode(node);
        deleteByteCodeHelpers();
    }
}

void CodeGenerator::generateByteCode(Node &node) {
    if(node.token == Node::OPERATOR){
        if(node == Node::OP_POSITIVE){
            generateByteCode(node,POSITIVE);
        }else if(node == Node::OP_NEGATIVE){
            generateByteCode(node,NEGATIVE);
        }else if(node == Node::OP_LOGICAL_NOT){
            generateByteCode(node,LOGICAL_NOT);
        }else if(node == Node::OP_MULTIPLICATION){
            generateByteCode(node,MULTIPLICATION);
        }else if(node == Node::OP_DEVIATION){
            generateByteCode(node,DEVIATION);
        }else if(node == Node::OP_PLUS){
            generateByteCode(node,PLUS);
        }else if(node == Node::OP_MINUS){
            generateByteCode(node,MINUS);
        }else if(node == Node::OP_GREATER_OR_EQUAL){
            generateByteCode(node,GREATER_OR_EQUAL);
        }else if(node == Node::OP_SMALLER_OR_EQUAL){
            generateByteCode(node,SMALLER_OR_EQUAL);
        }else if(node == Node::OP_GREATER){
            generateByteCode(node,GREATER);
        }else if(node == Node::OP_SMALLER){
            generateByteCode(node,SMALLER);
        }else if(node == Node::OP_EQUAL){
            generateByteCode(node,EQUAL);
        }else if(node == Node::OP_NOT_EQUAL){
            generateByteCode(node,NOT_EQUAL);
        }else if(node == Node::OP_LOGICAL_AND){
            generateByteCode(node,LOGICAL_AND);
        }else if(node == Node::OP_LOGICAL_OR){
            generateByteCode(node,LOGICAL_OR);
        }else if(node == Node::OP_ASSIGN){
            generateMoveByteCode(node);
        }
    }
    else if(node.token == Node::KEYWORD){
        if(node == Node::KW_PRINT) {
            generateByteCode(node,PRINT);
        }
    }
}

void CodeGenerator::generateByteCode(Node &node, Command command) {
    switch (node.specialToken) {
        case Node::OP_LEFT:
        case Node::OP_RIGHT:
            if(node.operands[0].operands.empty()){
                createHelperTo(node.operands[0]);
            }else{
                generateByteCode(node.operands[0]);
            }
            holder += command;
            setHelperName(lastHelper);
            if(node.token == Node::KEYWORD){
                deleteLastHelper();
            }
            break;
        case Node::OP_BOTH://order is matter
            if(node.operands[0].operands.empty()){
                createHelperTo(node.operands[0]);
                if(node.operands[1].operands.empty()){
                    if(node.operands[1].token == Node::ID){
                        holder += command;
                        setHelperName(lastHelper);
                        setCodeName(node.operands[1].str);
                    }else{
                        createHelperTo(node.operands[1]);
                        holder += command;
                        setHelperName(lastHelper-1);
                        setHelperName(lastHelper);
                        deleteLastHelper();
                    }
                }else{
                    generateByteCode(node.operands[1]);
                    holder += command;
                    setHelperName(lastHelper-1);
                    setHelperName(lastHelper);
                    deleteLastHelper();
                }
            }else if(node.operands[1].operands.empty()){
                generateByteCode(node.operands[0]);
                if(node.operands[1].token == Node::ID){
                    holder += command;
                    setHelperName(lastHelper);
                    setCodeName(node.operands[1].str);
                }else{
                    createHelperTo(node.operands[1]);
                    holder += command;
                    setHelperName(lastHelper-1);
                    setHelperName(lastHelper);
                    deleteLastHelper();
                }
            }else{
                generateByteCode(node.operands[0]);
                generateByteCode(node.operands[1]);
                holder += command;
                setHelperName(lastHelper-1);
                setHelperName(lastHelper);
                deleteLastHelper();
            }
            break;
        case Node::INVALID:
        case Node::OP_BETWEEN:
        default:
            throw std::runtime_error("CodeGenerator::generateByteCode");
    }
}

void CodeGenerator::generateMoveByteCode(Node &node) {
    if(node.operands[0].operands.empty() && node.operands[0].token == Node::ID) {
        if (node.operands[1].operands.empty()) {
            switch (node.operands[0].token) {
                case Node::STRING:
                    holder += MOVE_STRING;
                    setCodeName(node.operands[0].str);
                    setString(node.operands[1].str);
                    break;
                case Node::NUMBER:
                    holder += MOVE_NUMBER;
                    setCodeName(node.operands[0].str);
                    setNumber(node.operands[1].str);
                    break;
                case Node::BOOL:
                    holder += MOVE_BOOL;
                    setCodeName(node.operands[0].str);
                    setBool(node.operands[1].str);
                    break;
                case Node::ID:
                    holder += MOVE_VAR;
                    setCodeName(node.operands[0].str);
                    setCodeName(node.operands[1].str);
                default:
                    throw std::runtime_error("CodeGenerator::generateByteCode");
            }
            holder += MOVE_VAR;
            setHelperName(++lastHelper);
            setCodeName(node.operands[0].str);
        }else{
            generateByteCode(node.operands[1]);
            holder += MOVE_VAR;
            setCodeName(node.operands[0].str);
            setHelperName(lastHelper);
            //no need to delete helper
        }
    }else{
        throw std::runtime_error("CodeGenerator::generateByteCode");
    }
}

void CodeGenerator::createHelperTo(Node &node) {
    switch(node.token){
        case Node::ID:
            holder += MOVE_VAR;
            setHelperName(++lastHelper);
            setCodeName(node.str);
            break;
        case Node::STRING:
            holder += MOVE_STRING;
            setHelperName(++lastHelper);
            setString(node.str);
            break;
        case Node::NUMBER:
            holder += MOVE_NUMBER;
            setHelperName(++lastHelper);
            setNumber(node.str);
            break;
        case Node::BOOL:
            holder += MOVE_BOOL;
            setHelperName(++lastHelper);
            setBool(node.str);
            break;
        default:
            throw std::runtime_error("CodeGenerator::createHelperTo");
    }
}

void CodeGenerator::deleteLastHelper() {
    holder += static_cast<char>(DELETE);
    setHelperName(lastHelper--);

}

void CodeGenerator::setHelperName(int name) {
    setCodeName(std::to_string(name));
}

void CodeGenerator::deleteByteCodeHelpers() {
    while(lastHelper){
        deleteLastHelper();
    }
}

void CodeGenerator::setCodeName(const std::string &str) {
    holder += (char)str.size();
    holder += str;
}

void CodeGenerator::setString(const std::string &str) {
    holder += str.size();
    holder += str;
}

void CodeGenerator::setNumber(const std::string &str) {
    const Number number = stold(str);
    unsigned char temp[sizeof(Number)];
    std::copy(
            reinterpret_cast<const unsigned char*>(&number),
            reinterpret_cast<const unsigned char*>(&number) + sizeof(Number),
            &temp[0]
    );
    holder += std::string(reinterpret_cast<char*>(&temp),sizeof(Number) / sizeof(char));
}

void CodeGenerator::setBool(const std::string &str) {
    holder += (str == "true");
}
