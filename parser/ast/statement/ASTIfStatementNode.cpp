//
// Created by mark on 26/04/17.
//

#include "ASTIfStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTIfStatementNode::ASTIfStatementNode(std::unique_ptr<ASTExprNode> predicate,
                                                    std::unique_ptr<ASTBlockStatementNode> blockIfTrue,
                                                    std::unique_ptr<ASTBlockStatementNode> blockIfFalse) : predicate(
        std::move(predicate)), blockIfTrue(std::move(blockIfTrue)), blockIfFalse(std::move(blockIfFalse)) {}

parser::ast::ASTIfStatementNode::ASTIfStatementNode(std::unique_ptr<parser::ast::ASTExprNode> predicate,
                                                    std::unique_ptr<parser::ast::ASTBlockStatementNode> blockIfTrue)
        : predicate(std::move(predicate)), blockIfTrue(std::move(blockIfTrue)) {}

std::unique_ptr<parser::ast::ASTExprNode> & parser::ast::ASTIfStatementNode::getPredicate() {
    return predicate;
}

std::unique_ptr<parser::ast::ASTBlockStatementNode> & parser::ast::ASTIfStatementNode::getBlockIfTrue() {
    return blockIfTrue;
}

std::unique_ptr<parser::ast::ASTBlockStatementNode> & parser::ast::ASTIfStatementNode::getBlockIfFalse() {
    return blockIfFalse;
}

parser::ast::StatementType parser::ast::ASTIfStatementNode::getStatementType() {
    return IF;
}

void parser::ast::ASTIfStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
