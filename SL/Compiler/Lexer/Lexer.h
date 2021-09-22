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
        std::vector<std::vector<Node>> holder;
        std::vector<Node> primaryHolder;
    public:
        explicit Lexer(std::string);

        void clear();
    private:
        inline void push_clear(Node &);

        inline void push_clear_ifnempty(Node &);
    };
}//namespace SL



#endif //SL_LEXER_H
