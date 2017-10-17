//
// Created by mark on 21/03/17.
//

#include "TokenType.h"

lexer::TokenType lexer::Token::getToken() const {
    return token;
}

const std::string &lexer::Token::getAttribute() const {
    return attribute;
}

lexer::Token::Token(lexer::TokenType token, const std::string &value) : token(token), attribute(value) {}