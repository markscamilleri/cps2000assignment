/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170520.
 */

#include "Visitor.h"

void visitor::Visitor::visit(std::vector<std::unique_ptr<parser::ast::ASTNode>> &nodes) {
    for (std::vector<std::unique_ptr<parser::ast::ASTNode>>::iterator iterator = nodes.begin();
         iterator != nodes.end(); ++iterator) {
        (*iterator)->accept(this);
    }
}
