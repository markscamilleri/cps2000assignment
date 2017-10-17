
#include <vector>
#include <iostream>
#include "Compiler.h"
#include "visitor/XMLVisitor.h"
#include "parser/Parser.h"
#include "exceptions/Exception.h"
#include "visitor/TypeCheckVisitor.h"
#include "exceptions/TypeError.h"
#include "visitor/InterpreterVisitor.h"

std::unique_ptr<visitor::Visitor> xmlVisitor(new visitor::XMLVisitor());
std::unique_ptr<visitor::Visitor> typeCheckVisitor(new visitor::TypeCheckVisitor());
std::unique_ptr<visitor::InterpreterVisitor> interpreterVisitor(new visitor::InterpreterVisitor());

void printSymbolTable() {
    const std::vector<std::unique_ptr<std::map<std::string, visitor::helper::Symbol>>> &symbolTable = interpreterVisitor->getSymbolTable().getSymbolTable();

    for (std::vector<std::unique_ptr<std::map<std::string, visitor::helper::Symbol>>>::const_iterator iterator = symbolTable.begin();
         iterator != symbolTable.end(); ++iterator) {
        for (std::map<std::string, visitor::helper::Symbol>::const_iterator normalIterator = iterator->get()->begin();
             normalIterator != iterator->get()->end(); ++normalIterator) {
            std::cout << (*normalIterator).first << " ";

            switch ((*normalIterator).second.valueType){
                case visitor::helper::INTEGER:
                    std::cout << (*normalIterator).second.value.intValue;
                    break;
                case visitor::helper::REAL:
                    std::cout << (*normalIterator).second.value.realValue;
                    break;
                case visitor::helper::BOOLEAN:
                    std::cout << std::boolalpha << (*normalIterator).second.value.boolValue;
                    break;
                case visitor::helper::STRING:
                    std::cout << (*normalIterator).second.value.stringValue;
                    break;
                default:
                    break;
            }

            std::cout << std::endl;
        }
        std::cout << "=============================" << std::endl;
    }
}

int main() {
    std::string command;

    while (command.find("#exit") == std::string::npos) {
        std::cout << "MLi> ";

        std::cin >> command;
        if (command.find("#load_xml") != std::string::npos){
            std::vector<std::string> lines;
            try {
                std::cin >> command;
                compiler::Compiler::readInput(command, lines);
                parser::Parser parserObj(lines);

                std::vector<std::unique_ptr<parser::ast::ASTNode>> nodes = parserObj.parse();

                xmlVisitor->visit(nodes);
                std::cout << "--------------------------------------------" << std::endl;
                typeCheckVisitor->visit(nodes);
                interpreterVisitor->visit(nodes);

            } catch (exceptions::Exception &e) {
                std::cerr << e.getError() << std::endl;
            }

        } else if (command.find("#load") != std::string::npos) {
            std::vector<std::string> lines;
            try {
                std::cin >> command;
                compiler::Compiler::readInput(command, lines);
                parser::Parser parserObj(lines);

                std::vector<std::unique_ptr<parser::ast::ASTNode>> nodes = parserObj.parse();

                typeCheckVisitor->visit(nodes);
                interpreterVisitor->visit(nodes);

            } catch (exceptions::Exception &e) {
                std::cerr << e.getError() << std::endl;
            }
        } else if (command.find("#st") != std::string::npos) {
            printSymbolTable();
        } else {
            // Read commands and parse them.
        }

        std::cin.clear();
    }
}

