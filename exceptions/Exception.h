/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170501.
 */

#ifndef CPS2000_ASSIGNMENT_EXCEPTION_H
#define CPS2000_ASSIGNMENT_EXCEPTION_H

#include <exception>
#include <string>

namespace exceptions {
    class Exception: public std::exception {
    protected:
        std::string message;

    public:
        virtual const std::string getMessage() const;
        virtual const std::string getError() const = 0;

        const char *what() const throw() override;
    };
}


#endif //CPS2000_ASSIGNMENT_EXCEPTION_H
