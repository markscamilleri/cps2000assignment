/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#ifndef CPS2000_ASSIGNMENT_SCOPESYMBOLTABLE_H
#define CPS2000_ASSIGNMENT_SCOPESYMBOLTABLE_H

#include <map>
#include <ostream>
#include "../../parser/ast/statement/ASTVariableDeclStatementNode.h"
#include "../../parser/ast/statement/ASTFunctionDeclStatementNode.h"
#include "Symbol.h"

namespace visitor {
    namespace helper {
        class ScopedSymbolTable {
        private:
            /**
             * This represents the symbol table for the program
             * Each entry in the vector defines a scope.
             * The map is the symbol table for that scope.
             */
            std::vector<std::unique_ptr<std::map<std::string, Symbol>>> symbolTable;

        public:
            /**
             * Adds an entry to the symbol table at the last scope created.
             * @param identifier the identifier to add
             * @param type the identifier's type. if this is a function, it must be the return type.
             */
            void addEntryToSymbolTable(std::string identifier, SymbolType type);

            /**
             * Adds an entry to the symbol table at the last scope created.
             * @param identifier the identifier to add
             * @param intValue the integer value
             */
            void addEntryToSymbolTable(std::string identifier, int intValue);

            /**
             * Adds an entry to the symbol table at the last scope created.
             * @param identifier the identifier to add
             * @param realValue the real value
             */
            void addEntryToSymbolTable(std::string identifier, float realValue);

            /**
             * Adds an entry to the symbol table at the last scope created.
             * @param identifier the identifier to add
             * @param boolValue the Boolean Value
             */
            void addEntryToSymbolTable(std::string identifier, bool boolValue);

            /**
             * Adds an entry to the symbol table at the last scope created.
             * @param identifier the identifier to add
             * @param stringValue the string value
             */
            void addEntryToSymbolTable(std::string identifier, std::string stringValue);

            /**
             * Adds an entry to the symbol table at the last scope created when the type is unknown
             * but given to be correct
             * @param identifier the identifier to add
             * @param value the value
             */
            void addEntryToSymbolTable(std::string identifier,
                                       parser::ast::ASTFunctionDeclStatementNode *functionDeclStatementNode);

            /**
             * Adds an entry to the symbol table at the last scope created when the type is unknown
             * but given to be correct
             * @param identifier the identifier to add
             * @param value the value
             */
            void addEntryToSymbolTable(std::string identifier, Symbol value);

            /**
             * Adds a scope and creates a symbol table for it
             * @return true if sucessful, false otherwise
             */
            void addScope();

            /**
             * Removes the last scope from this symbol table, and all it's symbols
             */
            void popScope();

            /**
             * Checks whether the identifier given exists or not
             * @return true if the identifier is found, false otherwise
             */
            bool checkSymbolExists(std::string identifier);

            /**
             * Gets the type of the symbol. Throws a TypeError if the symbol is not found.
             * @return the SymbolType of the identifier
             */
            Symbol getSymbol(std::string identifier);

            /**
             * Changes an entry to the symbol table at the last scope it was created
             * @param identifier the identifier to change
             * @param value the value
             */
            void changeSymbolValue(std::string identifier, Symbol value);

            const std::vector<std::unique_ptr<std::map<std::string, Symbol>>> &getSymbolTable() const;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_SCOPESYMBOLTABLE_H
