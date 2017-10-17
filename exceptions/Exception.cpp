/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170501.
 */

#include "Exception.h"

const std::string exceptions::Exception::getMessage() const {
    return message;
}

const char *exceptions::Exception::what() const throw() {
    return getError().c_str();
}