//
// Created by a404m on 9/19/21.
//

#include "Runner.h"

#include <utility>

using namespace SL;

Runner::Runner(CodeGenerator c) : varHolder({}), code(std::move(c)) {
    Command command;
    std::string word,word2;
    for(it = code.holder.begin(),begin = it,end = code.holder.end();it < end;){
        command = (Command)(*it);
        ++it;
        switch (command) {
            case POSITIVE:
                getNextNameOrString(word);
                varHolder[word].positive();
                break;
            case NEGATIVE:
                getNextNameOrString(word);
                varHolder[word].negative();
                break;
            case MULTIPLICATION:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].multiplication(varHolder[word2]);
                break;
            case DEVIATION:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].deviation(varHolder[word2]);
                break;
            case PLUS:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].plus(varHolder[word2]);
                break;
            case MINUS:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].minus(varHolder[word2]);
                break;
            case EQUAL:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].equal(varHolder[word2]);
                break;
            case NOT_EQUAL:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].notEqual(varHolder[word2]);
                break;
            case MOVE_NUMBER: {
                getNextNameOrString(word);
                word2 = code.holder.substr(it - begin, sizeof(Number));
                it += sizeof(Number);
                auto num = reinterpret_cast<const Number *>(word2.c_str())[0];
                varHolder[word].move(Var(num));
            }
                break;
            case MOVE_STRING:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].move(Var(word2));
                break;
            case MOVE_BOOL:
                getNextNameOrString(word);
                varHolder[word].move(Var(*it == 1));
                ++it;
                break;
            case MOVE_VAR:
                getNextNameOrString(word);
                getNextNameOrString(word2);
                varHolder[word].move(varHolder[word2]);
                break;
            case DELETE:
                getNextNameOrString(word);
                varHolder.erase(word);
                break;
            case PRINT:
                getNextNameOrString(word);
                varHolder[word].print();
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
