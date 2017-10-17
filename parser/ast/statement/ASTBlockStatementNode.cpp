//
// Created by mark on 26/04/17.
//

#include "ASTBlockStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTBlockStatementNode::ASTBlockStatementNode(
        std::vector<std::unique_ptr<parser::ast::ASTStatementNode>> &contents) : blockContents() {
    std::vector<std::unique_ptr<parser::ast::ASTStatementNode>>::iterator iter = contents.begin();

    for (; iter != contents.end() ; iter++) {
        blockContents.push_back(std::move(*iter));
    }
}

parser::ast::ASTBlockStatementNode::ASTBlockStatementNode() {}

parser::ast::StatementType parser::ast::ASTBlockStatementNode::getStatementType() {
    return BLOCK_STATEMENT;
}

void parser::ast::ASTBlockStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
