//
// Created by a404m on 9/19/21.
//

#include "Runner.h"
#include <utility>

using namespace SL;

Runner::Runner(CodeGenerator c) : varHolder({}), code(std::move(c)),
                it(code.holder.begin()),begin(it),end(code.holder.end()) {
    Command command;
    std::string word1,word2;
    while(it < end){
        command = (Command)(*it);
        ++it;
        switch (command) {
            case POSITIVE:
                getNextNameOrString(word1);
                varHolder[word1].positive();
                break;
            case NEGATIVE:
                getNextNameOrString(word1);
                varHolder[word1].negative();
                break;
            case LOGICAL_NOT:
                getNextNameOrString(word1);
                varHolder[word1].logicalNot();
                break;
            case MULTIPLICATION:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].multiplication(varHolder[word2]);
                break;
            case DEVIATION:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].deviation(varHolder[word2]);
                break;
            case PLUS:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].plus(varHolder[word2]);
                break;
            case MINUS:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].minus(varHolder[word2]);
                break;
            case GREATER:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].greater(varHolder[word2]);
                break;
            case SMALLER:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].smaller(varHolder[word2]);
                break;
            case GREATER_OR_EQUAL:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].greaterOrEqual(varHolder[word2]);
                break;
            case SMALLER_OR_EQUAL:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].smallerOrEqual(varHolder[word2]);
                break;
            case EQUAL:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].equal(varHolder[word2]);
                break;
            case NOT_EQUAL:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].notEqual(varHolder[word2]);
                break;
            case LOGICAL_AND:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].logicalAnd(varHolder[word2]);
                break;
            case LOGICAL_OR:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].logicalOr(varHolder[word2]);
                break;
            case MOVE_NUMBER: {
                getNextNameOrString(word1);
                word2 = code.holder.substr(it - begin, sizeof(Number));
                it += sizeof(Number);
                auto num = reinterpret_cast<const Number *>(word2.c_str())[0];
                varHolder[word1].move(Var(num));
            }
                break;
            case MOVE_STRING:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].move(Var(word2));
                break;
            case MOVE_BOOL:
                getNextNameOrString(word1);
                varHolder[word1].move(Var(*it == 1));
                ++it;
                break;
            case MOVE_VAR:
                getNextNameOrString(word1);
                getNextNameOrString(word2);
                varHolder[word1].move(varHolder[word2]);
                break;
            case DELETE:
                getNextNameOrString(word1);
                varHolder.erase(word1);
                break;
            case PRINT:
                getNextNameOrString(word1);
                varHolder[word1].print();
                break;
            default:
                throw std::runtime_error("Runner::Runner");
        }
    }
}

void Runner::getNextNameOrString(std::string &str) {
    auto size = *it;
    ++it;
    str = code.holder.substr(it-begin,size);
    it += size;
}
