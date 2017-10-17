/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170501.
 */

#ifndef CPS2000_ASSIGNMENT_ILLEGALARGUMENTEXCEPTION_H
#define CPS2000_ASSIGNMENT_ILLEGALARGUMENTEXCEPTION_H


#include "Exception.h"

namespace exceptions {
    /**
     * Exception to show an illegal argument was given
     */
    class IllegalArgumentException : public Exception {
    private:
        /// The argument that's raised the exception
        std::string argument;
    public:
        /**
         * Constructor for this exception
         * @param message The error message
         * @param argument The argument that's raised the exception
         */
        IllegalArgumentException(const std::string message, const std::string &argument);

        /**
         * @return The argument that raised the exception
         */
        const std::string &getArgument() const;

        /**
         * @return The full error message
         */
        const std::string getError() const override;
    };
}

#endif //CPS2000_ASSIGNMENT_ILLEGALARGUMENTEXCEPTION_H
