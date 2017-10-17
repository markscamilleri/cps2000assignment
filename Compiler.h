//
// Created by mark on 27/04/17.
//

#ifndef CPS2000_ASSIGNMENT_COMPILER_H
#define CPS2000_ASSIGNMENT_COMPILER_H

#include <string>
#include <vector>

namespace compiler {
    class Compiler {
    public:
        static std::vector<std::string> &readInput(const std::string filename, std::vector<std::string> &lines);
    };
}


#endif //CPS2000_ASSIGNMENT_COMPILER_H
