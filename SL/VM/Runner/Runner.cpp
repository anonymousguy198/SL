//
// Created by a404m on 9/19/21.
//

#include "Runner.h"
#include <sstream>

using namespace SL;

Runner::Runner(const CodeGenerator& code) : varHolder({}) {
    Command command;
    std::string word;
    for(const auto& line : code.codeHolder){
        std::istringstream lineStream(line);
        std::string word2;
        lineStream >> word;
        command = (Command)(word[0]-code.SEPARATOR);
        switch (command) {
            case POSITIVE:
                lineStream >> word;
                varHolder[word].positive();
                break;
            case NEGATIVE:
                lineStream >> word;
                varHolder[word].negative();
                break;
            case MULTIPLICATION:
                lineStream >> word >> word2;
                varHolder[word].multiplication(varHolder[word2]);
                break;
            case DEVIATION:
                lineStream >> word >> word2;
                varHolder[word].deviation(varHolder[word2]);
                break;
            case PLUS:
                lineStream >> word >> word2;
                varHolder[word].plus(varHolder[word2]);
                break;
            case MINUS:
                lineStream >> word >> word2;
                varHolder[word].minus(varHolder[word2]);
                break;
            case EQUAL:
                lineStream >> word >> word2;
                varHolder[word].equal(varHolder[word2]);
                break;
            case NOT_EQUAL:
                lineStream >> word >> word2;
                varHolder[word].notEqual(varHolder[word2]);
                break;
            case MOVE_NUMBER:
                lineStream >> word >> word2;
                varHolder[word].move(Var(std::stold(word2)));
                break;
            case MOVE_STRING:
                lineStream >> word;
                getline(lineStream,word2);
                varHolder[word].move(Var(word2));
                break;
            case MOVE_BOOL:
                lineStream >> word >> word2;
                varHolder[word].move(Var(word2 == "true"));
                break;
            case MOVE_VAR:
                lineStream >> word >> word2;
                varHolder[word].move(varHolder[word2]);
                break;
            case DELETE:
                lineStream >> word;
                varHolder.erase(word);
                break;
            case PRINT:
                lineStream >> word;
                varHolder[word].print();
                break;
            default:
                throw std::runtime_error("Runner::Runner");
        }
    }
}