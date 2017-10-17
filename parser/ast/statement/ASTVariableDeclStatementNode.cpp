//
// Created by mark on 24/04/17.
//

#include "ASTVariableDeclStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTVariableDeclStatementNode::ASTVariableDeclStatementNode(std::unique_ptr<ASTIdentifierNode> identifier,
                                                                    parser::ast::VariableType type,
                                                                    std::unique_ptr<ASTExprNode> expr) : identifier(
        std::move(identifier)), type(type), expr(std::move(expr)) {}

std::unique_ptr<parser::ast::ASTIdentifierNode> &parser::ast::ASTVariableDeclStatementNode::getIdentifier() {
    return identifier;
}

parser::ast::VariableType parser::ast::ASTVariableDeclStatementNode::getType() const {
    return type;
}

std::unique_ptr<parser::ast::ASTExprNode> & parser::ast::ASTVariableDeclStatementNode::getExpr() {
    return expr;
}

parser::ast::StatementType parser::ast::ASTVariableDeclStatementNode::getStatementType() {
    return VARIABLE_DECL;
}

void parser::ast::ASTVariableDeclStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
