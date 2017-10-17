/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#include "TypeError.h"

exceptions::TypeError::TypeError(const std::string message, const std::string identifier) : identifier(identifier) {
    Exception::message = message;
}

exceptions::TypeError::TypeError(const std::string message) : identifier("") {
    Exception::message = message;
}

const std::string exceptions::TypeError::getError() const {
    if (identifier.empty()) {
        return getMessage();
    } else {
        return getMessage() + " " + getIdentifier();
    }
}

const std::string &exceptions::TypeError::getIdentifier() const {
    return identifier;
}



