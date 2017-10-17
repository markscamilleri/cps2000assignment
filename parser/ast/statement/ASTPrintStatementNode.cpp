//
// Created by mark on 26/04/17.
//
#include "ASTPrintStatementNode.h"
#include "../../../visitor/Visitor.h"


parser::ast::ASTPrintStatementNode::ASTPrintStatementNode(std::unique_ptr<ASTExprNode> expr) : expr(std::move(expr)) {}

std::unique_ptr<parser::ast::ASTExprNode> & parser::ast::ASTPrintStatementNode::getExpr() {
    return expr;
}

parser::ast::StatementType parser::ast::ASTPrintStatementNode::getStatementType() {
    return PRINT;
}

void parser::ast::ASTPrintStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}

