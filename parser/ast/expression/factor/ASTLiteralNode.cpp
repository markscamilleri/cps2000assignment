/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170503.
 */

#include "ASTLiteralNode.h"
#include "../../../../visitor/Visitor.h"

template<typename T>
parser::ast::FactorType parser::ast::ASTLiteralNode<T>::getFactorType() {
    return LITERAL;
}

template<typename T>
parser::ast::ASTLiteralNode<T>::ASTLiteralNode(T literal) : literal(literal) {}

template<typename T>
T parser::ast::ASTLiteralNode<T>::getLiteral() const {
    return literal;
}

template<typename T>
void parser::ast::ASTLiteralNode<T>::accept(visitor::Visitor *visitor) {
    visitor->visit(this);
}
