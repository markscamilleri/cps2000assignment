//
// Created by mark on 21/03/17.
//

#include "FileIOException.h"

exceptions::FileIOException::FileIOException(std::string message, std::string filename) : filename(filename) {
    Exception::message = message;
}

const std::string exceptions::FileIOException::getFilename() const {
    return filename;
}

const std::string exceptions::FileIOException::getError() const {
    return getMessage() + " with file name " + getFilename();
}
