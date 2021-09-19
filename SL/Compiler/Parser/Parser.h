//
// Created by a404m on 9/19/21.
//

#ifndef SL_PARSER_H
#define SL_PARSER_H


#include "../Lexer/Lexer.h"
#include <map>

namespace SL {
    class Parser {
        friend class CodeGenerator;
    private:
        std::vector<std::vector<Node>> primaryHolder;
        std::vector<Node> secondaryHolder;
        const std::vector<std::vector<Node>> orders{
                {
                        Node{"(",Node::BLOCK,Node::OP_BETWEEN}
                },{
                        Node{"+",Node::OPERATOR,Node::OP_RIGHT},
                        Node{"-",Node::OPERATOR,Node::OP_RIGHT}
                },{
                        Node{"*",Node::OPERATOR,Node::OP_BOTH},
                        Node{"/",Node::OPERATOR,Node::OP_BOTH}
                },{
                        Node{"+",Node::OPERATOR,Node::OP_BOTH},
                        Node{"-",Node::OPERATOR,Node::OP_BOTH}
                },{
                        Node{"==",Node::OPERATOR,Node::OP_BOTH},
                        Node{"!=",Node::OPERATOR,Node::OP_BOTH}
                },{
                        Node{"=",Node::OPERATOR,Node::OP_BOTH}
                },{
                        Node{"print",Node::KEYWORD,Node::OP_RIGHT}
                }
        };
    public:
        explicit Parser(Lexer);

    private:
        Node parseLine(std::vector<Node>&);

        static void setOperatorKind(const std::vector<Node>::iterator &,const std::vector<Node>::iterator &,const std::vector<Node>::iterator &);
        static bool isOperand(const Node&);
        static std::vector<Node>::const_iterator isInBy_string_token(const std::vector<Node> &, const std::vector<Node>::const_iterator &);
    };
}


#endif //SL_PARSER_H
