/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503.
 */

#include <iostream>
#include "ASTFunctionCallNode.h"
#include "../../../../visitor/Visitor.h"

parser::ast::ASTFunctionCallNode::ASTFunctionCallNode(std::unique_ptr<ASTIdentifierNode> identifier,
                                                      std::vector<std::unique_ptr<ASTExprNode>> &actualParams)
        : identifier(std::move(identifier)), actualParams() {

    std::vector<std::unique_ptr<parser::ast::ASTExprNode>>::iterator iter;
    iter = actualParams.begin();

    for (; iter != actualParams.end(); iter++) {
        ASTFunctionCallNode::actualParams.push_back(std::move(*iter));
    }

}


parser::ast::ASTFunctionCallNode::ASTFunctionCallNode(std::unique_ptr<ASTIdentifierNode> identifier)
        : identifier(std::move(identifier)) {}

parser::ast::FactorType parser::ast::ASTFunctionCallNode::getFactorType() {
    return FUNCTION_CALL;
}

std::unique_ptr<parser::ast::ASTIdentifierNode> &parser::ast::ASTFunctionCallNode::getIdentifier() {
    return identifier;
}

std::vector<std::unique_ptr<parser::ast::ASTExprNode>> &parser::ast::ASTFunctionCallNode::getActualParams() {
    return actualParams;
}

void parser::ast::ASTFunctionCallNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
