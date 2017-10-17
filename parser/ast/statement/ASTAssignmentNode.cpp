//
// Created by mark on 26/04/17.
//

#include "ASTAssignmentNode.h"
#include "../../../visitor/Visitor.h"


parser::ast::ASTAssignmentNode::ASTAssignmentNode(std::unique_ptr<parser::ast::ASTIdentifierNode> identifier, std::unique_ptr<ASTExprNode> expr)
        : identifier(std::move(identifier)), expr(std::move(expr)) {}

std::unique_ptr<parser::ast::ASTExprNode> &parser::ast::ASTAssignmentNode::getExpr() {
    return expr;
}

std::unique_ptr<parser::ast::ASTIdentifierNode> & parser::ast::ASTAssignmentNode::getIdentifier() {
    return identifier;
}

parser::ast::StatementType parser::ast::ASTAssignmentNode::getStatementType() {
    return ASSIGNMENT;
}

void parser::ast::ASTAssignmentNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
