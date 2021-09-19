//
// Created by a404m on 9/19/21.
//

#ifndef SL_LEXER_H
#define SL_LEXER_H


#include "../Node/Node.h"

namespace SL {
    class Lexer {
        friend class Parser;
    private:
        std::vector<Node> holder;
    public:
        explicit Lexer(std::string);

        void clear();
    private:
        void push_clear(Node &);

        void push_clear_ifnempty(Node &);
    };
}//namespace SL



#endif //SL_LEXER_H
