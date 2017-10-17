/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170501.
 */

#include "IllegalArgumentException.h"

exceptions::IllegalArgumentException::IllegalArgumentException(const std::string message, const std::string &argument)
        : argument(argument) {
    Exception::message = message;
}

const std::string &exceptions::IllegalArgumentException::getArgument() const {
    return argument;
}

const std::string exceptions::IllegalArgumentException::getError() const {
    return getMessage() + " on argument " + getArgument();
}