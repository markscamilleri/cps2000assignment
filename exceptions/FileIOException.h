//
// Created by mark on 21/03/17.
//

#ifndef CPS2000_ASSIGNMENT_FILEIOEXCEPTION_H
#define CPS2000_ASSIGNMENT_FILEIOEXCEPTION_H

#include "Exception.h"

namespace exceptions {
    class FileIOException : public Exception {
    private:
        std::string filename;

    public:
        FileIOException(std::string message, std::string filename);

        const std::string getFilename() const;

        const std::string getError() const override;
    };
}
#endif //CPS2000_ASSIGNMENT_FILEIOEXCEPTION_H
