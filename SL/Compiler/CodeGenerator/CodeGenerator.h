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
        std::string holder;
        int lastHelper;

        static const Node OP_POSITIVE;
        static const Node OP_NEGATIVE;

        static const Node OP_MULTIPLICATION;
        static const Node OP_DEVIATION;

        static const Node OP_PLUS;
        static const Node OP_MINUS;

        static const Node OP_GREATER;
        static const Node OP_SMALLER;
        static const Node OP_GREATER_OR_EQUAL;
        static const Node OP_SMALLER_OR_EQUAL;

        static const Node OP_EQUAL;
        static const Node OP_NOT_EQUAL;

        static const Node OP_ASSIGN;

        static const Node KW_PRINT;
    public:
        explicit CodeGenerator(Parser);

    private:
        void generateByteCode(Node&);
        void generateByteCode(Node&,Command);
        void generateMoveByteCode(Node&);
        void createHelperTo(Node&);
        void deleteLastHelper();
        inline void setHelperName(int);
        inline void deleteByteCodeHelpers();
        inline void setCodeName(const std::string &str);
        inline void setString(const std::string &);
        inline void setNumber(const std::string &);
        inline void setBool(const std::string &);
    };
}//namespace SL


#endif //SL_CODEGENERATOR_H
