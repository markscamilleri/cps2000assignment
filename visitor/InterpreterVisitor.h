/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170520.
 */

#ifndef CPS2000_ASSIGNMENT_INTERPRETERVISITOR_H
#define CPS2000_ASSIGNMENT_INTERPRETERVISITOR_H

#include "Visitor.h"
#include "helpers/ScopedSymbolTable.h"

namespace visitor {
    class InterpreterVisitor: public Visitor {
    private:
        /**
         * The symbol table which can store values
         */
        helper::ScopedSymbolTable symbolTable;

        /**
         * The answer of the stack (makes more sense to store it seperately than in the symbol table)
         */
        helper::Symbol stackAns;

        bool isReturn = false;

    public:
        InterpreterVisitor();

        InterpreterVisitor(const helper::ScopedSymbolTable &symbolTable, const helper::Symbol &stackAns, bool isReturn);

        void visit(parser::ast::ASTExprNode *node) override;

        void visit(parser::ast::ASTSimpleExprNode *node) override;

        void visit(parser::ast::ASTTermNode *node) override;

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

        void visit(std::vector<std::unique_ptr<parser::ast::ASTNode>> &nodes) override;

        const helper::ScopedSymbolTable &getSymbolTable() const;
    };
}

#endif //CPS2000_ASSIGNMENT_INTERPRETERVISITOR_H
