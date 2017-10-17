/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170520.
 */

#ifndef CPS2000_ASSIGNMENT_SYMBOL_H
#define CPS2000_ASSIGNMENT_SYMBOL_H


#include "../../parser/ast/statement/ASTFunctionDeclStatementNode.h"

namespace visitor{
    namespace helper{
        typedef parser::ast::VariableType SymbolType;

        enum WHICH_VALUE {
            TYPE,
            INTEGER,
            REAL,
            BOOLEAN,
            STRING,
            FUNCTION
        };

        struct Symbol {
            WHICH_VALUE valueType;

            union Value {
                SymbolType type;
                int intValue;
                float realValue;
                bool boolValue;
                std::string *stringValue;
                parser::ast::ASTFunctionDeclStatementNode *fnValue;

                Value(SymbolType type) : type(type) {}

                Value(int intValue) : intValue(intValue) {}

                Value(float realValue) : realValue(realValue) {}

                Value(bool boolValue) : boolValue(boolValue) {}

                Value(std::string *stringValue) : stringValue(stringValue) {}

                Value(parser::ast::ASTFunctionDeclStatementNode *fnValue) : fnValue(fnValue) {}
            } value;

            Symbol(WHICH_VALUE valueType, Value value) : valueType(valueType), value(value) {}

            Symbol(SymbolType value) : valueType(TYPE), value(value) {}

            Symbol(int value) : valueType(INTEGER), value(value) {}

            Symbol(bool value) : valueType(BOOLEAN), value(value) {}

            Symbol(float value) : valueType(REAL), value(value) {}

            Symbol(std::string *value) : valueType(STRING), value(value) {}

            Symbol(parser::ast::ASTFunctionDeclStatementNode *value) : valueType(FUNCTION), value(value) {}
        };
    }
}

#endif //CPS2000_ASSIGNMENT_SYMBOL_H
