/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170426
 */

#ifndef CPS2000_ASSIGNMENT_TOKENS_H
#define CPS2000_ASSIGNMENT_TOKENS_H

#include <string>

namespace lexer {
    /// The possible tokens that can be returned by the lexer
    enum TokenType {
        TOK_IDENTIFIER,
        TOK_INTEGER_LITERAL,
        TOK_REAL_LITERAL,
        TOK_BOOL_LITERAL,
        TOK_STRING_LITERAL,
        TOK_ADDITION,
        TOK_SUBTRACTION,
        TOK_MULTIPLICATION,
        TOK_DIVISION,
        TOK_RELATIONAL_OP,
        TOK_ASSIGNMENT_EQUALS,
        TOK_SINGLE_LINE_COMMENT,
        TOK_MULTI_LINE_COMMENT,
        TOK_PUNCTUATION,
        TOK_AND,
        TOK_OR,
        TOK_NOT,
        TOK_IF,
        TOK_ELSE,
        TOK_WHILE,
        TOK_TYPE,
        TOK_SET,
        TOK_VAR,
        TOK_PRINT,
        TOK_DEF,
        TOK_RETURN,
        TOK_EOF
    };

    /**
     * Token class that stores the enum Token and the attribute that made up this token.
     * This could be a value, identifier etc...
     */
    class Token {
    private:
        /// The token itself
        TokenType token;
        /// The attribute that made up the token
        std::string attribute;

    public:
        /**
         * @param token The token type
         * @param value The attribute that made up this token
         */
        Token(TokenType token, const std::string &value);

        /**
         * @return The token
         */
        TokenType getToken() const;

        /**
         * @return The attribute
         */
        const std::string &getAttribute() const;
    };
}  // namespace lexer


#endif //CPS2000_ASSIGNMENT_TOKENS_H
