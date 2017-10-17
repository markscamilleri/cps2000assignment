/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170520.
 */

#include <iostream>
#include "InterpreterVisitor.h"

visitor::InterpreterVisitor::InterpreterVisitor() : symbolTable(), stackAns(0), isReturn(false) {}

void visitor::InterpreterVisitor::visit(parser::ast::ASTExprNode *node) {
    node->getLeft()->accept(this);

    if (node->getRight()) {
        helper::Symbol e1 = stackAns;
        node->getRight()->accept(this);
        helper::Symbol e2 = stackAns;
        switch (node->getRelationalOperator()) {
            case parser::ast::REL_GREATER:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue > e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue > e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue > e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) > *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::REL_GREATER_OR_EQUALS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue >= e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue >= e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue >= e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) >= *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::REL_EQUALS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue == e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue == e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue == e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) == *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::REL_NOT_EQUALS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue != e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue != e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue != e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) != *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::REL_LESS_OR_EQUALS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue <= e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue <= e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue <= e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) <= *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::REL_LESS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue < e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue < e2.value.realValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue < e2.value.boolValue);
                        break;
                    case helper::STRING:
                        stackAns = (*(e1.value.stringValue) < *(e2.value.stringValue));
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTSimpleExprNode *node) {
    node->getLeft()->accept(this);

    if (node->getRight()) {
        helper::Symbol e1 = stackAns;
        node->getRight()->accept(this);
        helper::Symbol e2 = stackAns;

        switch (node->getAddOp()) {
            case parser::ast::PLUS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue + e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue + e2.value.realValue);
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::MINUS:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue - e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue - e2.value.realValue);
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::OR:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue | e2.value.intValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue || e2.value.boolValue);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTTermNode *node) {
    node->getLeft()->accept(this);

    if (node->getRight()) {
        helper::Symbol e1 = stackAns;
        node->getRight()->accept(this);
        helper::Symbol e2 = stackAns;

        switch (node->getOp()) {
            case parser::ast::MULTIPLICATION:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue * e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue * e2.value.realValue);
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::DIVISION:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue / e2.value.intValue);
                        break;
                    case helper::REAL:
                        stackAns = (e1.value.realValue / e2.value.realValue);
                        break;
                    default:
                        break;
                }
                break;
            case parser::ast::AND:
                switch(stackAns.valueType){
                    case helper::INTEGER:
                        stackAns = (e1.value.intValue & e2.value.intValue);
                        break;
                    case helper::BOOLEAN:
                        stackAns = (e1.value.boolValue && e2.value.boolValue);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTLiteralNode<int> *node) {
    stackAns = node->getLiteral();
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTLiteralNode<float> *node) {
    stackAns = node->getLiteral();
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTLiteralNode<bool> *node) {
    stackAns = node->getLiteral();
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTLiteralNode<std::string> *node) {
    stackAns = new std::string(node->getLiteral());
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTFunctionCallNode *node) {
    symbolTable.addScope();
    parser::ast::ASTFunctionDeclStatementNode *fnValue = symbolTable.getSymbol(
            node->getIdentifier()->getName()).value.fnValue;

    // Push parameters to the "stack"
    for (unsigned int i = 0; i < node->getActualParams().size(); i++) {
        node->getActualParams()[i]->accept(this);
        symbolTable.addEntryToSymbolTable(fnValue->getFormalParams()[i].first->getName(), stackAns);
    }

    fnValue->getBlock()->accept(this);

    isReturn = false;
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTIdentifierNode *node) {
    stackAns = symbolTable.getSymbol(node->getName());
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTSubExpression *node) {
    node->getExpr()->accept(this);
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTUnaryNode *node) {
    node->getExpr()->accept(this);
    helper::Symbol symb = stackAns;

    switch (node->getOp()) {
        case parser::ast::NEGATIVE:
            switch(symb.valueType){
                case helper::INTEGER:
                    stackAns = -1 * symb.value.intValue;
                    break;
                case helper::REAL:
                    stackAns = -1 * symb.value.realValue;
                    break;
                default:
                    break;
            }
            break;
        case parser::ast::NOT:
            switch (symb.valueType){
                case helper::BOOLEAN:
                    stackAns = !symb.value.boolValue;
                default:
                    break;
            }
            break;
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTAssignmentNode *node) {
    node->getExpr()->accept(this);
    symbolTable.changeSymbolValue(node->getIdentifier()->getName(), stackAns);
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTVariableDeclStatementNode *node) {
    node->getExpr()->accept(this);
    symbolTable.addEntryToSymbolTable(node->getIdentifier()->getName(), stackAns);
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTBlockStatementNode *node) {
    symbolTable.addScope();

    for (std::vector<std::unique_ptr<parser::ast::ASTStatementNode>>::iterator iterator = node->blockContents.begin();
         iterator != node->blockContents.end() && !isReturn; ++iterator) {
        (*iterator)->accept(this);
    }

    symbolTable.popScope();
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTFunctionDeclStatementNode *node) {
    symbolTable.addEntryToSymbolTable(node->getIdentifier()->getName(), node);
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTIfStatementNode *node) {
    node->getPredicate()->accept(this);
    if(stackAns.value.boolValue){
        node->getBlockIfTrue()->accept(this);
    } else if(node->getBlockIfFalse()) {
        node->getBlockIfFalse()->accept(this);
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTWhileStatementNode *node) {
    node->getPredicate()->accept(this);
    while(stackAns.value.boolValue){
        node->getLoopBlock()->accept(this);
        node->getPredicate()->accept(this);
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTPrintStatementNode *node) {
    node->getExpr()->accept(this);
    switch(stackAns.valueType) {
        case helper::INTEGER:
            std::cout << stackAns.value.intValue << std::endl;
            break;
        case helper::REAL:
            std::cout << stackAns.value.realValue << std::endl;
            break;
        case helper::BOOLEAN:
            std::cout << std::boolalpha << stackAns.value.boolValue << std::endl;
            break;
        case helper::STRING:
            std::cout << *(stackAns.value.stringValue) << std::endl;
            break;
        default:
            break;
    }
}

void visitor::InterpreterVisitor::visit(parser::ast::ASTReturnStatementNode *node) {
    node->getExpr()->accept(this);
    isReturn = true;
}

void visitor::InterpreterVisitor::visit(std::vector<std::unique_ptr<parser::ast::ASTNode>> &nodes) {
    Visitor::visit(nodes);
}

const visitor::helper::ScopedSymbolTable &visitor::InterpreterVisitor::getSymbolTable() const {
    return symbolTable;
}
