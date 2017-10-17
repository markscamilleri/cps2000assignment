/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170426
 */

#ifndef CPS2000_ASSIGNMENT_SYNTAXERROR_H
#define CPS2000_ASSIGNMENT_SYNTAXERROR_H

#include "Exception.h"

namespace exceptions {
    /**
     * An exception that would be thrown if the lexer is unable to tokenize a lexeme
     * This is also thrown if the parser can't parse the token
     */
    class SyntaxError : public Exception {
    private:
        /// The line number where the syntax error occurred
        long lineNo;
        /// The column number where the syntax error occurred
        long charNo;

    public:
        /**
         * Constructor for this exception
         * @param message The error message
         * @param lineNo  The line number where this syntax error occurred
         * @param charNo  The character number where this syntax error occurred
         */
        SyntaxError(const std::string message, long lineNo, long charNo);

        /**
         * @return The line number this error occurred
         */
        long getLineNo() const;

        /**
         * @return The character number this error occurred
         */
        long getCharNo() const;

        /**
         * @return The full error message (message + position)
         */
        const std::string getError() const override ;
    };
}

#endif //CPS2000_ASSIGNMENT_SYNTAXERROR_H
