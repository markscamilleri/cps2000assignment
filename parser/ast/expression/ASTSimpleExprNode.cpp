//
// Created by mark on 28/04/17.
//

#include "ASTSimpleExprNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTSimpleExprNode::ASTSimpleExprNode(std::unique_ptr<ASTTermNode> left) : left(std::move(left)) {}

parser::ast::ASTSimpleExprNode::ASTSimpleExprNode(std::unique_ptr<ASTTermNode> left,
                                                  parser::ast::AdditiveOp addOp,
                                                  std::unique_ptr<ASTTermNode> right) : left(std::move(left)),
                                                                                        addOp(addOp),
                                                                                        right(std::move(right)) {}

std::unique_ptr<parser::ast::ASTTermNode> & parser::ast::ASTSimpleExprNode::getLeft() {
    return left;
}

parser::ast::AdditiveOp parser::ast::ASTSimpleExprNode::getAddOp() {
    return addOp;
}

std::unique_ptr<parser::ast::ASTTermNode> & parser::ast::ASTSimpleExprNode::getRight() {
    return right;
}

std::string parser::ast::ASTSimpleExprNode::getAdditiveOperatorString() {
    switch(addOp){
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case OR:
            return "or";
        default:
            return std::string();
    }
}

void parser::ast::ASTSimpleExprNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
