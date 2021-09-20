//
// Created by a404m on 9/19/21.
//

#ifndef SL_CODEGENERATOR_H
#define SL_CODEGENERATOR_H


#include "../Parser/Parser.h"
#include "../additional/enums.h"

namespace SL {
    class CodeGenerator {
        friend class Runner;
    private:
        std::vector<std::string> codeHolder;
        int lastHelper;

        const char SEPARATOR;

        static const Node OP_POSITIVE;
        static const Node OP_NEGATIVE;

        static const Node OP_MULTIPLICATION;
        static const Node OP_DEVIATION;

        static const Node OP_PLUS;
        static const Node OP_MINUS;

        static const Node OP_EQUAL;
        static const Node OP_NOT_EQUAL;

        static const Node OP_ASSIGN;

        static const Node KW_PRINT;
    public:
        explicit CodeGenerator(Parser);

    private:
        void generateByteCode(Node&);
        static std::string getHelperName(int);
        void generateByteCode(Node&,Command);
        void generateMoveByteCode(Node&);
        void createHelperTo(Node&);
        void deleteLastHelper();
        void deleteByteCodeHelpers();
        void generateByteCommand(Command,const std::string& = "",const std::string& = "");
    };
}//namespace SL


#endif //SL_CODEGENERATOR_H
