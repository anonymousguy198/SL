//
// Created by a404m on 9/19/21.
//

#include "CodeGenerator.h"

using namespace SL;

const Node CodeGenerator::OP_POSITIVE = Node{"+", Node::OPERATOR, Node::OP_RIGHT};
const Node CodeGenerator::OP_NEGATIVE = Node{"-", Node::OPERATOR, Node::OP_RIGHT};
const Node CodeGenerator::OP_MULTIPLICATION = Node{"*", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_DEVIATION = Node{"/", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_PLUS = Node{"+", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_MINUS = Node{"-", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_EQUAL = Node{"==", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_NOT_EQUAL = Node{"!=", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::OP_ASSIGN = Node{"=", Node::OPERATOR, Node::OP_BOTH};
const Node CodeGenerator::KW_PRINT = Node{"print", Node::KEYWORD, Node::OP_RIGHT};

CodeGenerator::CodeGenerator(Parser parser) : codeHolder({}), lastHelper(0), SEPARATOR(' ') {
    for(auto& node : parser.secondaryHolder){
        generateByteCode(node);
        deleteByteCodeHelpers();
    }
}

void CodeGenerator::generateByteCode(Node &node) {
    if(node.token == Node::OPERATOR){
        if(node == OP_POSITIVE){
            generateByteCode(node,POSITIVE);
        }else if(node == OP_NEGATIVE){
            generateByteCode(node,NEGATIVE);
        }else if(node == OP_MULTIPLICATION){
            generateByteCode(node,MULTIPLICATION);
        }else if(node == OP_DEVIATION){
            generateByteCode(node,DEVIATION);
        }else if(node == OP_PLUS){
            generateByteCode(node,PLUS);
        }else if(node == OP_MINUS){
            generateByteCode(node,MINUS);
        }else if(node == OP_EQUAL){
            generateByteCode(node,EQUAL);
        }else if(node == OP_NOT_EQUAL){
            generateByteCode(node,NOT_EQUAL);
        }else if(node == OP_ASSIGN){
            std::string line;
            if(node.operands[0].operands.empty() && node.operands[0].token == Node::ID) {
                if (node.operands[1].operands.empty()) {
                    line = std::to_string(MOVE) + " ";
                    line += node.operands[0].str;
                    line += SEPARATOR;
                    line += node.operands[1].str;
                    codeHolder.push_back(line);
                    line = std::to_string(MOVE) + " ";
                    line += getHelperName(++lastHelper);
                    line += SEPARATOR;
                    line += node.operands[0].str;
                } else {
                    generateByteCode(node.operands[1]);
                    line = std::to_string(MOVE) + " ";
                    line += node.operands[0].str;
                    line += SEPARATOR;
                    line += getHelperName(lastHelper);
                    //no need to delete helper
                }
            }else{
                throw std::runtime_error("CodeGenerator::generateByteCode");
            }
            codeHolder.push_back(line);
        }
    }
    else if(node.token == Node::KEYWORD){
        if(node == KW_PRINT) {
            generateByteCode(node,PRINT);
        }
    }
}

std::string CodeGenerator::getHelperName(int name) {
    return "$"+ std::to_string(name);
}

void CodeGenerator::generateByteCode(Node &node, Command command) {
    std::string line;
    switch (node.specialToken) {
        case Node::OP_LEFT:
        case Node::OP_RIGHT:
            if(node.operands[0].operands.empty()){
                line = std::to_string(MOVE)+" ";
                line += getHelperName(++lastHelper);
                line += SEPARATOR;
                line += node.operands[0].str;
                codeHolder.push_back(line);
                line = std::to_string(command)+" ";
                line += getHelperName(lastHelper);
            }else{
                generateByteCode(node.operands[0]);
                line = std::to_string(command)+" ";
                line += getHelperName(lastHelper);
            }
            codeHolder.push_back(line);
            if(node.token == Node::KEYWORD){
                line = std::to_string(DELETE)+" ";
                line += getHelperName(lastHelper--);
                codeHolder.push_back(line);
            }
            break;
        case Node::OP_BOTH://order is matter
            if(node.operands[0].operands.empty()){
                if(node.operands[1].operands.empty()){
                    line = std::to_string(MOVE)+" ";
                    line += getHelperName(++lastHelper);
                    line += SEPARATOR;
                    line += node.operands[0].str;
                    codeHolder.push_back(line);
                    line = std::to_string(command)+" ";
                    line += getHelperName(lastHelper);
                    line += SEPARATOR;
                    line += node.operands[1].str;
                }else{
                    generateByteCode(node.operands[1]);
                    line = std::to_string(MOVE)+" ";//order is matter (in operator overloading)
                    line += getHelperName(++lastHelper);
                    line += SEPARATOR;
                    line += node.operands[0].str;
                    codeHolder.push_back(line);
                    line = std::to_string(command)+" ";
                    line += getHelperName(lastHelper);
                    line += SEPARATOR;
                    line += getHelperName(lastHelper-1);
                    codeHolder.push_back(line);
                    line = std::to_string(MOVE)+" ";
                    line += getHelperName(lastHelper-1);
                    line += SEPARATOR;
                    line += getHelperName(lastHelper);
                    codeHolder.push_back(line);
                    line = std::to_string(DELETE)+" ";
                    line += getHelperName(lastHelper--);
                }
            }else if(node.operands[1].operands.empty()){
                generateByteCode(node.operands[0]);
                line = std::to_string(command)+" ";
                line += getHelperName(lastHelper);
                line += SEPARATOR;
                line += node.operands[1].str;
            }else{
                generateByteCode(node.operands[1]);
                generateByteCode(node.operands[0]);
                line = std::to_string(command)+" ";
                line += getHelperName(lastHelper-1);
                line += SEPARATOR;
                line += getHelperName(lastHelper);
                codeHolder.push_back(line);
                line = std::to_string(DELETE)+" ";
                line += getHelperName(lastHelper--);
            }
            codeHolder.push_back(line);
            break;
        case Node::INVALID:
        case Node::OP_BETWEEN:
        default:
            throw std::runtime_error("CodeGenerator::generateByteCode");
    }
}

void CodeGenerator::deleteByteCodeHelpers() {
    std::string line = std::to_string(DELETE) + " ";
    while(lastHelper){
        codeHolder.push_back(line + getHelperName(lastHelper--));
    }
}