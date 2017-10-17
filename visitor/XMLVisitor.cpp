/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170518.
 */

#include "XMLVisitor.h"
#include <iostream>

void visitor::XMLVisitor::visit(parser::ast::ASTExprNode *node) {


    if (node->getRight()) {
        std::cout << indentations << "<Expression RelationalOp=\"" << node->getRelOpString() << "\">" << std::endl;

        addIndentation();

        node->getLeft()->accept(this);

        node->getRight()->accept(this);
    } else {
        std::cout << indentations << "<Expression>" << std::endl;

        addIndentation();

        node->getLeft()->accept(this);
    }

    removeIndentation();

    std::cout << indentations << "</Expression>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTSimpleExprNode *node) {

    if (node->getRight()) {
        std::cout << indentations << "<SimpleExpression Op=\"" << node->getAdditiveOperatorString() << "\">"
                  << std::endl;

        addIndentation();

        node->getLeft()->accept(this);
        node->getRight()->accept(this);
    } else {
        std::cout << indentations << "<SimpleExpression>" << std::endl;

        addIndentation();
        node->getLeft()->accept(this);
    }

    removeIndentation();

    std::cout << indentations << "</SimpleExpression>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTTermNode *node) {
    if (node->getRight()) {
        std::cout << indentations << "<Term Op=\"" << node->getMutliplicativeOpString() << "\">" << std::endl;
        addIndentation();

        node->getLeft()->accept(this);
        node->getRight()->accept(this);
    } else {
        std::cout << indentations << "<Term>" << std::endl;
        addIndentation();

        node->getLeft()->accept(this);
    }

    removeIndentation();
    std::cout << indentations << "</Term>" << std::endl;
}

template <typename T>
void visitor::XMLVisitor::genericVisit(parser::ast::ASTLiteralNode<T> *node) {
    std::cout << std::boolalpha << indentations << "<Literal>" << node->getLiteral() << "</Literal>"
              << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTLiteralNode<int> *node){
    genericVisit(node);
}

void visitor::XMLVisitor::visit(parser::ast::ASTLiteralNode<float> *node){
    genericVisit(node);
}

void visitor::XMLVisitor::visit(parser::ast::ASTLiteralNode<bool> *node) {
    genericVisit(node);
}

void visitor::XMLVisitor::visit(parser::ast::ASTLiteralNode<std::string> *node){
    genericVisit(node);
}


void visitor::XMLVisitor::visit(parser::ast::ASTFunctionCallNode *node) {
    std::cout << indentations << "<FunctionCall>" << std::endl;
    addIndentation();
    std::cout << indentations << "<ActualParams>" << std::endl;

    addIndentation();
    for (std::vector<std::unique_ptr<parser::ast::ASTExprNode>>::iterator iter = node->getActualParams().begin();
         iter != node->getActualParams().end(); ++iter) {
        (*iter)->accept(this);
    }

    std::cout << indentations << "</ActualParams>" << std::endl;
    removeIndentation();
    std::cout << indentations << "</FunctionCall>" << std::endl;

    removeIndentation();
}

void visitor::XMLVisitor::visit(parser::ast::ASTIdentifierNode *node) {
    std::cout << indentations << "<Identifier>" << node->getName() << "</Identifier>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTSubExpression *node) {
    node->getExpr()->accept(this);
}

void visitor::XMLVisitor::visit(parser::ast::ASTUnaryNode *node) {
    std::cout << indentations << "<UnaryExpression Op=\"" << node->getOpString() << "\">" << std::endl;
    addIndentation();

    node->getExpr()->accept(this);

    removeIndentation();
    std::cout << indentations << "</UnaryExpression>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTAssignmentNode *node) {
    std::cout << indentations << "<Assignment>" << std::endl;
    addIndentation();

    node->getIdentifier()->accept(this);
    node->getExpr()->accept(this);

    removeIndentation();
    std::cout << indentations << "</Assignment>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTVariableDeclStatementNode *node) {
    std::cout << indentations << "<VariableDeclaration type=\""
              << parser::ast::getVariableTypeString(node->getType()) + "\">" << std::endl;

    addIndentation();
    node->getIdentifier()->accept(this);
    node->getExpr()->accept(this);
    removeIndentation();

    std::cout << indentations << "</VariableDeclaration>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTBlockStatementNode *node) {
    std::cout << indentations + "<Block>" << std::endl;

    addIndentation();
    for (std::vector<std::unique_ptr<parser::ast::ASTStatementNode>>::iterator iterator = node->blockContents.begin();
         iterator != node->blockContents.end(); ++iterator) {
        (*iterator)->accept(this);
    }
    removeIndentation();

    std::cout << indentations << "</Block>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTFunctionDeclStatementNode *node) {
    std::cout << indentations + "<FunctionDeclaration ReturnType=\""
              << parser::ast::getVariableTypeString(node->getReturnType()) << "\">" << std::endl;

    addIndentation();
    node->getIdentifier()->accept(this);
    node->getBlock()->accept(this);
    removeIndentation();

    std::cout << indentations << "</FunctionDeclaration>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTIfStatementNode *node) {
    std::cout << indentations << "<If>" << std::endl;

    addIndentation();
    node->getPredicate()->accept(this);
    node->getBlockIfTrue()->accept(this);
    node->getBlockIfFalse()->accept(this);
    removeIndentation();

    std::cout << indentations << "</If>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTWhileStatementNode *node) {
    std::cout << indentations << "<While>" << std::endl;

    addIndentation();
    node->getPredicate()->accept(this);
    node->getLoopBlock()->accept(this);
    removeIndentation();

    std::cout << indentations << "</While>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTPrintStatementNode *node) {
    std::cout << indentations << "<Print>" << std::endl;

    addIndentation();
    node->getExpr()->accept(this);
    removeIndentation();

    std::cout << "</Print>" << std::endl;
}

void visitor::XMLVisitor::visit(parser::ast::ASTReturnStatementNode *node) {
    std::cout << indentations + "<Return>" << std::endl;

    addIndentation();
    node->getExpr()->accept(this);
    removeIndentation();

    std::cout << indentations << "</Return>" << std::endl;
}

void visitor::XMLVisitor::addIndentation() {
    indentations.push_back('\t');
}

void visitor::XMLVisitor::removeIndentation() {
    if (!indentations.empty()) {
        indentations.pop_back();
    }
}
