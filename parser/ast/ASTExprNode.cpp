//
// Created by mark on 13/03/17.
//

#include "ASTExprNode.h"
#include "../../visitor/Visitor.h"


parser::ast::ASTExprNode::ASTExprNode(std::unique_ptr<ASTSimpleExprNode> left,
                                      parser::ast::RelOpType relationalOperator,
                                      std::unique_ptr<ASTSimpleExprNode> right) : left(std::move(left)),
                                                                                  relationalOperator(
                                                                                          relationalOperator),
                                                                                  right(std::move(right)) {}

parser::ast::ASTExprNode::ASTExprNode(std::unique_ptr<ASTSimpleExprNode> left) : left(std::move(left)) {}

const std::unique_ptr<parser::ast::ASTSimpleExprNode> &parser::ast::ASTExprNode::getLeft() const {
    return left;
}

parser::ast::RelOpType parser::ast::ASTExprNode::getRelationalOperator() const {
    return relationalOperator;
}

const std::unique_ptr<parser::ast::ASTSimpleExprNode> &parser::ast::ASTExprNode::getRight() const {
    return right;
}

const std::string parser::ast::ASTExprNode::getRelOpString() const {
    switch (relationalOperator) {
        case REL_EQUALS:
            return "EQUALS";
        case REL_GREATER:
            return "GREATER THAN";
        case REL_GREATER_OR_EQUALS:
            return "GREATER THAN OR EQUALS";
        case REL_LESS:
            return "LESS THAN";
        case REL_LESS_OR_EQUALS:
            return "LESS THAN OR EQUALS";
        case REL_NOT_EQUALS:
            return "NOT EQUALS";
        default:
            return "";
    }
}

void parser::ast::ASTExprNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}

