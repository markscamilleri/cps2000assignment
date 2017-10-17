//
// Created by mark on 07/04/17.
//

#include "SyntaxError.h"

exceptions::SyntaxError::SyntaxError(const std::string message, long lineNo, long charNo) : lineNo(lineNo + 1),
                                                                                       charNo(charNo) {
    Exception::message = message;
}


long exceptions::SyntaxError::getLineNo() const {
    return lineNo;
}

long exceptions::SyntaxError::getCharNo() const {
    return charNo;
}

const std::string exceptions::SyntaxError::getError() const {
    return getMessage() + " at line " + std::to_string(getLineNo()) + " and column " + std::to_string(getCharNo());
}