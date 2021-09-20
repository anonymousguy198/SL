//
// Created by a404m on 9/19/21.
//

#include "Var.h"

using namespace SL;

Var::Var(const String &str) : type(STRING), holder(str) {/*empty*/}

Var::Var(const Number &num) : type(NUMBER), holder(num) {/*empty*/}

Var::Var(Bool b) : type(BOOL), holder(b) {/*empty*/}

Var::Var(const Var &var) = default;

void Var::positive() {
    switch (type) {
        case NUMBER:
            holder = +std::get<Number>(holder);
            break;
        default:
            throw std::runtime_error("Var::positive");
    }
}

void Var::negative() {
    switch (type) {
        case NUMBER:
            holder = -std::get<Number>(holder);
            break;
        default:
            throw std::runtime_error("Var::negative");
    }
}

void Var::multiplication(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) *= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::deviation(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) /= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::plus(const Var &var) {
    if(type == var.type){
        if(type == NUMBER){
            std::get<Number>(holder) += std::get<Number>(var.holder);
        }else if(type == STRING){
            std::get<String>(holder) += std::get<String>(var.holder);
        }else{
            goto THROW;
        }
    }else{
        THROW:throw std::runtime_error("Var::");
    }
}

void Var::minus(const Var &var) {
    if(type == var.type && type == NUMBER){
        std::get<Number>(holder) -= std::get<Number>(var.holder);
    }else{
        throw std::runtime_error("Var::");
    }
}

void Var::equal(const Var &var) {
    *this = Var(type == var.type && holder == var.holder);
}

void Var::notEqual(const Var &var) {
    *this = Var(type != var.type || holder != var.holder);
}

void Var::move(const Var &var) {
    holder = var.holder;
    type = var.type;
}

#include <sstream>
extern std::ostringstream ss{};

void Var::print() {
    switch (type) {
        case STRING:
            ss << std::get<String>(holder);
            break;
        case NUMBER:
            ss << std::get<Number>(holder);
            break;
        case BOOL:
            ss << (std::get<Bool>(holder)? "true" : "false");
            break;
        default:
            throw std::runtime_error("Var::print");
    }
}
