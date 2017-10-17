//
// Created by mark on 26/04/17.
//

#include "ASTWhileStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTWhileStatementNode::ASTWhileStatementNode(std::unique_ptr<ASTExprNode> predicate,
                                                          std::unique_ptr<ASTBlockStatementNode> loopBlock)
        : predicate(std::move(predicate)), loopBlock(std::move(loopBlock)) {}

std::unique_ptr<parser::ast::ASTBlockStatementNode> & parser::ast::ASTWhileStatementNode::getLoopBlock() {
    return loopBlock;
}

std::unique_ptr<parser::ast::ASTExprNode> & parser::ast::ASTWhileStatementNode::getPredicate() {
    return predicate;
}

parser::ast::StatementType parser::ast::ASTWhileStatementNode::getStatementType() {
    return WHILE;
}

void parser::ast::ASTWhileStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
