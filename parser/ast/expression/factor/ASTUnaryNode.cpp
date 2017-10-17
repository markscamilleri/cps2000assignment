/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170505.
 */

#include "ASTUnaryNode.h"
#include "../../../../visitor/Visitor.h"

parser::ast::ASTUnaryNode::ASTUnaryNode(parser::ast::UnaryOperator op, std::unique_ptr<ASTExprNode> expr) : op(op),
                                                                                                            expr(std::move(
                                                                                                                    expr)) {}

parser::ast::UnaryOperator parser::ast::ASTUnaryNode::getOp() const {
    return op;
}

const std::unique_ptr<parser::ast::ASTExprNode> &parser::ast::ASTUnaryNode::getExpr() const {
    return expr;
}

const std::string parser::ast::ASTUnaryNode::getOpString() const {
    switch(op){
        case NEGATIVE:
            return "-";
        case NOT:
            return "not";
    }
}

parser::ast::FactorType parser::ast::ASTUnaryNode::getFactorType() {
    return UNARY;
}

void parser::ast::ASTUnaryNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
