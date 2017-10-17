/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#ifndef CPS2000_ASSIGNMENT_TYPEERROR_H
#define CPS2000_ASSIGNMENT_TYPEERROR_H

#include "Exception.h"

namespace exceptions {
    class TypeError: public Exception {
    private:

        /// Identifier with whcih this exception occured
        std::string identifier;
    public:
        TypeError(const std::string message, const std::string identifier);

        TypeError(const std::string message);

        const std::string &getIdentifier() const;

        /**
         * @return The full error message (message + identifier)
         */
        const std::string getError() const override ;
    };
}


#endif //CPS2000_ASSIGNMENT_TYPEERROR_H
