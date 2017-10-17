//
// Created by mark on 27/04/17.
//

#include <iostream>
#include <fstream>
#include "Compiler.h"
#include "exceptions/FileIOException.h"

std::vector<std::string> &compiler::Compiler::readInput(const std::string filename,
                                                        std::vector<std::string> &lines) {
    std::ifstream inputFile;

    inputFile.open(filename, std::ios::in);

    if (!inputFile.is_open()) {
        throw exceptions::FileIOException("The file was not opened", filename);
    }

    while (!inputFile.eof()) {
        std::string line;
        getline(inputFile, line);
        lines.push_back(line + "\n"); //Needed to put back the newline character that is removed in getline()
    };

    return lines;
}
