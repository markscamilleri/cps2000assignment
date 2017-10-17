/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#include "TypeCheckVisitor.h"
#include "../exceptions/TypeError.h"

void visitor::TypeCheckVisitor::visit(parser::ast::ASTExprNode *node) {
    node->getLeft()->accept(this);
    helper::SymbolType type1 = type;

    if (node->getRight()) {
        node->getRight()->accept(this);
        helper::SymbolType type2 = type;

        assertTypeMatch(type1, type2);
        assertTypeMismatch(type2, helper::SymbolType::STRING);
        type = helper::SymbolType::BOOLEAN;
    }
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTSimpleExprNode *node) {
    node->getLeft()->accept(this);
    helper::SymbolType type1 = type;

    if (node->getRight()) {
        node->getRight()->accept(this);
        helper::SymbolType type2 = type;

        assertTypeMatch(type1, type2);
        assertOperatorTypeMatch(type, node->getAddOp());
    }
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTTermNode *node) {
    node->getLeft()->accept(this);
    helper::SymbolType type1 = type;

    if (node->getRight()) {
        node->getRight()->accept(this);
        helper::SymbolType type2 = type;

        assertTypeMatch(type1, type2);
        assertOperatorTypeMatch(type, node->getOp());
    }
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTLiteralNode<int> *node) {
    type = helper::SymbolType::INTEGER;
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTLiteralNode<float> *node) {
    type = helper::SymbolType::REAL;
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTLiteralNode<bool> *node) {
    type = helper::SymbolType::BOOLEAN;
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTLiteralNode<std::string> *node) {
    type = helper::SymbolType::STRING;
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTFunctionCallNode *node) {
    node->getIdentifier()->accept(this);

    for (int i = 0; i < node->getActualParams().size(); ++i) {
        node->getActualParams()[i]->accept(this);

        std::string paramName = node->getIdentifier()->getName() + "|" + std::to_string(i);
        if(symbolTable.checkSymbolExists(paramName)) {
            assertTypeMatch(type, symbolTable.getSymbol(paramName).value.type);
        } else {
            throw exceptions::TypeError("Undefined argument", std::to_string(i+1));
        }
    }
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTIdentifierNode *node) {
    type = symbolTable.getSymbol(node->getName()).value.type;
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTSubExpression *node) {
    node->getExpr()->accept(this);
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTUnaryNode *node) {
    node->getExpr()->accept(this);
    assertOperatorTypeMatch(type, node->getOp());
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTAssignmentNode *node) {
    helper::SymbolType type1 = symbolTable.getSymbol(node->getIdentifier()->getName()).value.type;

    node->getExpr()->accept(this);
    helper::SymbolType type2 = type;

    assertTypeMatch(type1, type2);
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTVariableDeclStatementNode *node) {
    symbolTable.addEntryToSymbolTable(node->getIdentifier()->getName(), node->getType());
    node->getExpr()->accept(this);
    assertTypeMatch(type, node->getType());
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTBlockStatementNode *node) {
    symbolTable.addScope();

    for (std::vector<std::unique_ptr<parser::ast::ASTStatementNode>>::iterator iter = node->blockContents.begin();
         iter != node->blockContents.end(); ++iter) {
        (*iter)->accept(this);
    }

    symbolTable.popScope();
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTFunctionDeclStatementNode *node) {
    symbolTable.addEntryToSymbolTable(node->getIdentifier()->getName(), node->getReturnType());

    for (int i = 0; i < node->getFormalParams().size(); ++i) {
        symbolTable.addEntryToSymbolTable(node->getIdentifier()->getName() + "|" + std::to_string(i),
                                          node->getFormalParams()[i].second);
    }

    symbolTable.addScope();

    symbolTable.addEntryToSymbolTable(RETURN_VAR, node->getReturnType());
    for (std::vector<std::pair<std::unique_ptr<parser::ast::ASTIdentifierNode>, parser::ast::VariableType>>::iterator param = node->getFormalParams().begin();
         param != node->getFormalParams().end(); ++param) {
        symbolTable.addEntryToSymbolTable(param->first->getName(), param->second);
    }

    node->getBlock()->accept(this);
    symbolTable.popScope();
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTIfStatementNode *node) {
    node->getPredicate()->accept(this);
    assertTypeMatch(type, helper::SymbolType::BOOLEAN);

    node->getBlockIfTrue()->accept(this);
    if (node->getBlockIfFalse()) {
        node->getBlockIfFalse()->accept(this);
    }
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTWhileStatementNode *node) {
    node->getPredicate()->accept(this);
    assertTypeMatch(type, helper::SymbolType::BOOLEAN);

    node->getLoopBlock()->accept(this);
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTPrintStatementNode *node) {
    node->getExpr()->accept(this);
}

void visitor::TypeCheckVisitor::visit(parser::ast::ASTReturnStatementNode *node) {
    node->getExpr()->accept(this);

    assertReturnTypeMatch(type);
}


void visitor::TypeCheckVisitor::assertTypeMatch(visitor::helper::SymbolType type1, visitor::helper::SymbolType type2) {
    if (type1 != type2)
        throw exceptions::TypeError("Type mismatch exception");
}

void
visitor::TypeCheckVisitor::assertTypeMismatch(visitor::helper::SymbolType type1, visitor::helper::SymbolType type2) {
    if (type1 == type2)
        throw exceptions::TypeError("Type mismatch exception");
}


void visitor::TypeCheckVisitor::assertOperatorTypeMatch(visitor::helper::SymbolType type,
                                                        parser::ast::MultiplicativeOp multiplicativeOp) {
    switch (multiplicativeOp) {
        case parser::ast::MULTIPLICATION:
        case parser::ast::DIVISION:
            assertTypeMismatch(type, helper::SymbolType::BOOLEAN);
            assertTypeMismatch(type, helper::SymbolType::STRING);
            break;
        case parser::ast::AND:
            assertTypeMatch(type, helper::SymbolType::BOOLEAN);
            break;
    }
}

void visitor::TypeCheckVisitor::assertOperatorTypeMatch(visitor::helper::SymbolType type,
                                                        parser::ast::AdditiveOp additiveOp) {
    switch (additiveOp) {
        case parser::ast::PLUS:
        case parser::ast::MINUS:
            assertTypeMismatch(type, helper::SymbolType::BOOLEAN);
            assertTypeMismatch(type, helper::SymbolType::STRING);
            break;
        case parser::ast::OR:
            assertTypeMatch(type, helper::SymbolType::BOOLEAN);
            break;
    }
}

void visitor::TypeCheckVisitor::assertOperatorTypeMatch(visitor::helper::SymbolType type,
                                                        parser::ast::UnaryOperator unaryOperator) {
    switch (unaryOperator) {
        case parser::ast::NEGATIVE:
            assertTypeMismatch(type, helper::SymbolType::BOOLEAN);
            assertTypeMismatch(type, helper::SymbolType::STRING);
            break;
        case parser::ast::NOT:
            assertTypeMatch(type, helper::SymbolType::BOOLEAN);
            break;
    }
}

void visitor::TypeCheckVisitor::assertReturnTypeMatch(helper::SymbolType type) {
    if (type != symbolTable.getSymbol(RETURN_VAR).value.type)
        throw exceptions::TypeError("Return type mismatch exception");
}

void visitor::TypeCheckVisitor::visit(std::vector<std::unique_ptr<parser::ast::ASTNode>> &nodes) {
    symbolTable.addScope();
    Visitor::visit(nodes);
    symbolTable.popScope();
}
