//
// Created by a404m on 9/19/21.
//

#ifndef SL_ENUMS_H
#define SL_ENUMS_H

namespace SL {
    enum Command {
        POSITIVE = 1,
        NEGATIVE,
        MULTIPLICATION,
        DEVIATION,
        PLUS,
        MINUS,
        GREATER,
        SMALLER,
        GREATER_OR_EQUAL,
        SMALLER_OR_EQUAL,
        EQUAL,
        NOT_EQUAL,
        MOVE_NUMBER,
        MOVE_STRING,
        MOVE_BOOL,
        MOVE_VAR,
        DELETE,
        PRINT
    };
}//namespace SL

#endif //SL_ENUMS_H
