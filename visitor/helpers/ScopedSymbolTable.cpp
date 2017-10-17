/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#include "ScopedSymbolTable.h"
#include "../../exceptions/SyntaxError.h"
#include "../../exceptions/TypeError.h"

void
visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, visitor::helper::SymbolType type) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempType(type);

    if (!symbolTable.back()->emplace(identifier, tempType).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}

void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, int intValue) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(intValue);

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }

}

void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, float realValue) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(realValue);

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}

void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, bool boolValue) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(boolValue);

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}

void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, std::string stringValue) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(new std::string(stringValue));

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}


void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier,
                                                               parser::ast::ASTFunctionDeclStatementNode *functionDeclStatementNode) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(functionDeclStatementNode);

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}


void visitor::helper::ScopedSymbolTable::addEntryToSymbolTable(std::string identifier, visitor::helper::Symbol value) {
    if (symbolTable.empty()) {
        addScope();
    }

    Symbol tempValue(value);

    if (!symbolTable.back()->emplace(identifier, tempValue).second) {
        throw exceptions::TypeError("Symbol already exists", identifier);
    }
}

void visitor::helper::ScopedSymbolTable::addScope() {
    symbolTable.push_back(std::unique_ptr<std::map<std::string, Symbol>>(new std::map<std::string, Symbol>()));
    symbolTable.rbegin() = symbolTable.rbegin();
}

void visitor::helper::ScopedSymbolTable::popScope() {
    if (!symbolTable.empty()) {
        symbolTable.pop_back();
        symbolTable.rbegin() = symbolTable.rbegin();
    }
}

visitor::helper::Symbol visitor::helper::ScopedSymbolTable::getSymbol(std::string identifier) {
    for (std::vector<std::unique_ptr<std::map<std::string, Symbol>>>::reverse_iterator it = symbolTable.rbegin();
         it != symbolTable.rend(); it++) {
        std::map<std::string, Symbol>::iterator tuple = (*it)->find(identifier);
        if (tuple != (*it)->end()) return tuple->second;
    }

    throw exceptions::TypeError("Undefined symbol:", identifier);
}

bool visitor::helper::ScopedSymbolTable::checkSymbolExists(std::string identifier) {
    for (std::vector<std::unique_ptr<std::map<std::string, Symbol>>>::reverse_iterator it = symbolTable.rbegin();
         it != symbolTable.rend(); it++) {
        std::map<std::string, Symbol>::iterator tuple = (*it)->find(identifier);
        if (tuple != (*it)->end()) return true;
    }

    return false;
}

void visitor::helper::ScopedSymbolTable::changeSymbolValue(std::string identifier, visitor::helper::Symbol value) {
    for (std::vector<std::unique_ptr<std::map<std::string, Symbol>>>::reverse_iterator it = symbolTable.rbegin();
         it != symbolTable.rend(); it++) {
        std::map<std::string, Symbol>::iterator tuple = (*it)->find(identifier);
        if (tuple != (*it)->end()){
            tuple->second = value;
            return;
        }
    }

    throw exceptions::TypeError("Undefined symbol:", identifier);
}

const std::vector<std::unique_ptr<std::map<std::string, visitor::helper::Symbol>>> &
visitor::helper::ScopedSymbolTable::getSymbolTable() const {
    return symbolTable;
}
