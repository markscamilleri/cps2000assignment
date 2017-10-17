/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170518.
 */

#ifndef CPS2000_ASSIGNMENT_XMLVISITOR_H
#define CPS2000_ASSIGNMENT_XMLVISITOR_H

#include "Visitor.h"

namespace visitor {
    /**
     * visit() operators in this class
     */
    class XMLVisitor : public Visitor {
    private:

        /// Indentations to be prefixed to the xml
        std::string indentations = "";

        /// Increments the number of indentations by 1
        void addIndentation();

        /// Decrements the number of indentations by 1
        void removeIndentation();

    public:
        void visit(parser::ast::ASTExprNode *node) override;

        void visit(parser::ast::ASTSimpleExprNode *node) override;

        void visit(parser::ast::ASTTermNode *node) override;

        template<typename T> void genericVisit(parser::ast::ASTLiteralNode<T> *node);

        void visit(parser::ast::ASTLiteralNode<int> *node) override;

        void visit(parser::ast::ASTLiteralNode<float> *node) override;

        void visit(parser::ast::ASTLiteralNode<bool> *node) override;

        void visit(parser::ast::ASTLiteralNode<std::string> *node) override;

        void visit(parser::ast::ASTFunctionCallNode *node) override;

        void visit(parser::ast::ASTIdentifierNode *node) override;

        void visit(parser::ast::ASTSubExpression *node) override;

        void visit(parser::ast::ASTUnaryNode *node) override;

        void visit(parser::ast::ASTAssignmentNode *node) override;

        void visit(parser::ast::ASTVariableDeclStatementNode *node) override;

        void visit(parser::ast::ASTBlockStatementNode *node) override;

        void visit(parser::ast::ASTFunctionDeclStatementNode *node) override;

        void visit(parser::ast::ASTIfStatementNode *node) override;

        void visit(parser::ast::ASTWhileStatementNode *node) override;

        void visit(parser::ast::ASTPrintStatementNode *node) override;

        void visit(parser::ast::ASTReturnStatementNode *node) override;
    };
}

#endif //CPS2000_ASSIGNMENT_XMLVISITOR_H
