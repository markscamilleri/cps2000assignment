/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503.
 */

#include <iostream>
#include "ASTIdentifierNode.h"
#include "../../../../visitor/Visitor.h"

parser::ast::ASTIdentifierNode::ASTIdentifierNode(const std::string name) : name(name) {}

const std::string parser::ast::ASTIdentifierNode::getName() const {
    return name;
}
parser::ast::FactorType parser::ast::ASTIdentifierNode::getFactorType() {
    return IDENTIFIER;
}

void parser::ast::ASTIdentifierNode::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
