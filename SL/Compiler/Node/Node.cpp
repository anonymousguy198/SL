//
// Created by a404m on 9/19/21.
//

#include "Node.h"

using namespace SL;

Node::Node(std::string s, Token t, SpecialToken sp, std::initializer_list<Node> il) : str(std::move(s)), token(t), specialToken(sp), operands(il) {/*empty*/}

void Node::clear() {
    token = NONE;
    str.clear();
    operands.clear();
}

bool Node::isEmpty() const{
    return token == NONE;
}

bool Node::operator==(const Node &node) const {
    return this->str == node.str && this->token == node.token && this->specialToken == node.specialToken;
}

bool Node::operator!=(const Node &node) const {
    return this->str != node.str || this->token != node.token || this->specialToken != node.specialToken;
}

bool Node::operator>(const Node &node) const {///@todo find a better algorithm
    std::string t = this->str + std::to_string(this->token) + std::to_string(this->specialToken),
            n = node.str + std::to_string(node.token) + std::to_string(node.specialToken);
    return t > n;
}

bool Node::operator<(const Node &node) const {///@todo find a better algorithm
    std::string t = this->str + std::to_string(this->token) + std::to_string(this->specialToken),
            n = node.str + std::to_string(node.token) + std::to_string(node.specialToken);
    return t < n;
}

bool Node::operator>=(const Node &node) const {
    return !(*this < node);
}

bool Node::operator<=(const Node &node) const {
    return !(*this > node);
}