//
// Created by a404m on 9/19/21.
//

#ifndef SL_ENUMS_H
#define SL_ENUMS_H

namespace SL {
    enum Command {
        POSITIVE = 0,
        NEGATIVE,
        LOGICAL_NOT,
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
        LOGICAL_AND,
        LOGICAL_OR,
        MOVE_NUMBER,
        MOVE_STRING,
        MOVE_BOOL,
        MOVE_VAR,
        DELETE,
        PRINT,
        NATIVE_CALL
    };
}//namespace SL

#endif //SL_ENUMS_H
