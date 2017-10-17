//
// Created by mark on 28/04/17.
//

#include "ASTTermNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTTermNode::ASTTermNode(std::unique_ptr<ASTFactorNode> left,
                                      parser::ast::MultiplicativeOp op,
                                      std::unique_ptr<ASTFactorNode> right) : left(std::move(left)), op(op),
                                                                              right(std::move(right)) {}

parser::ast::ASTTermNode::ASTTermNode(std::unique_ptr<ASTFactorNode> left) : left(std::move(left)) {}

const std::unique_ptr<parser::ast::ASTFactorNode> &parser::ast::ASTTermNode::getLeft() const {
    return left;
}

parser::ast::MultiplicativeOp parser::ast::ASTTermNode::getOp() const {
    return op;
}

const std::unique_ptr<parser::ast::ASTFactorNode> &parser::ast::ASTTermNode::getRight() const {
    return right;
}

const std::string parser::ast::ASTTermNode::getMutliplicativeOpString() const {
    switch(op) {
        case MULTIPLICATION:
            return "*";
        case DIVISION:
            return "/";
        case AND:
            return "and";
        default:
            return std::string();
    }
}

void parser::ast::ASTTermNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
