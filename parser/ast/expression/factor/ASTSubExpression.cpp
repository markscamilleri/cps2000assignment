/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503.
 */

#include "ASTSubExpression.h"
#include "../../../../visitor/Visitor.h"

parser::ast::ASTSubExpression::ASTSubExpression(std::unique_ptr<ASTExprNode> expr) : expr(std::move(expr)) {}

parser::ast::FactorType parser::ast::ASTSubExpression::getFactorType() {
    return SUB_EXPRESSION;
}

const std::unique_ptr<parser::ast::ASTExprNode> &parser::ast::ASTSubExpression::getExpr() const {
    return expr;
}

void parser::ast::ASTSubExpression::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
