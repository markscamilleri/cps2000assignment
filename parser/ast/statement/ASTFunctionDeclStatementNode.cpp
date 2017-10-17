//
// Created by mark on 26/04/17.
//

#include "ASTFunctionDeclStatementNode.h"
#include "../../../visitor/Visitor.h"

parser::ast::ASTFunctionDeclStatementNode::ASTFunctionDeclStatementNode(
        std::unique_ptr<parser::ast::ASTIdentifierNode> identifier,
        std::vector<std::pair<std::unique_ptr<parser::ast::ASTIdentifierNode>, VariableType>> &params,
        VariableType returnType,
        std::unique_ptr<ASTBlockStatementNode> block) : identifier(std::move(identifier)), formalParams(),
                                                        returnType(returnType), block(std::move(block)) {

    std::vector<std::pair<std::unique_ptr<parser::ast::ASTIdentifierNode>, parser::ast::VariableType>>::iterator iter = params.begin();

    for (; iter != params.end(); iter++) {
        formalParams.push_back(std::move(*iter));
    }
}

std::unique_ptr<parser::ast::ASTIdentifierNode> &parser::ast::ASTFunctionDeclStatementNode::getIdentifier() {
    return identifier;
}

std::vector<std::pair<std::unique_ptr<parser::ast::ASTIdentifierNode>, parser::ast::VariableType>> &
parser::ast::ASTFunctionDeclStatementNode::getFormalParams() {
    return formalParams;
}

parser::ast::VariableType parser::ast::ASTFunctionDeclStatementNode::getReturnType() {
    return returnType;
}

std::unique_ptr<parser::ast::ASTBlockStatementNode> &parser::ast::ASTFunctionDeclStatementNode::getBlock() {
    return block;
}

parser::ast::StatementType parser::ast::ASTFunctionDeclStatementNode::getStatementType() {
    return FUNCTION_DECL;
}

void parser::ast::ASTFunctionDeclStatementNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
