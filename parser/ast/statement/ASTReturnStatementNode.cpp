//
// Created by mark on 26/04/17.
//

#include "ASTReturnStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTReturnStatementNode::ASTReturnStatementNode(std::unique_ptr<ASTExprNode> expr)
        : expr(std::move(expr)) {}

std::unique_ptr<parser::ast::ASTExprNode> & parser::ast::ASTReturnStatementNode::getExpr() {
    return expr;
}

parser::ast::StatementType parser::ast::ASTReturnStatementNode::getStatementType() {
    return RETURN;
}

void parser::ast::ASTReturnStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}