/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170511.
 */

#ifndef CPS2000_ASSIGNMENT_VISITOR_H
#define CPS2000_ASSIGNMENT_VISITOR_H

#include <string>
#include <memory>
#include "../parser/ast/expression/factor/ASTLiteralNode.h"
#include "../parser/ast/expression/factor/ASTFunctionCallNode.h"
#include "../parser/ast/expression/factor/ASTSubExpression.h"
#include "../parser/ast/expression/factor/ASTUnaryNode.h"
#include "../parser/ast/statement/ASTAssignmentNode.h"
#include "../parser/ast/statement/ASTVariableDeclStatementNode.h"
#include "../parser/ast/statement/ASTBlockStatementNode.h"
#include "../parser/ast/statement/ASTFunctionDeclStatementNode.h"
#include "../parser/ast/statement/ASTIfStatementNode.h"
#include "../parser/ast/statement/ASTWhileStatementNode.h"
#include "../parser/ast/statement/ASTPrintStatementNode.h"
#include "../parser/ast/statement/ASTReturnStatementNode.h"


namespace visitor {
    class Visitor {
    public:
        virtual void visit(parser::ast::ASTExprNode *node)=0;

        virtual void visit(parser::ast::ASTSimpleExprNode *node)=0;

        virtual void visit(parser::ast::ASTTermNode *node)=0;

        virtual void visit(parser::ast::ASTLiteralNode<int> *node)=0;

        virtual void visit(parser::ast::ASTLiteralNode<float> *node)=0;

        virtual void visit(parser::ast::ASTLiteralNode<bool> *node)=0;

        virtual void visit(parser::ast::ASTLiteralNode <std::string> *node)=0;

        virtual void visit(parser::ast::ASTFunctionCallNode *node)=0;

        virtual void visit(parser::ast::ASTIdentifierNode *node)=0;

        virtual void visit(parser::ast::ASTSubExpression *node)=0;

        virtual void visit(parser::ast::ASTUnaryNode *node)=0;

        virtual void visit(parser::ast::ASTAssignmentNode *node)=0;

        virtual void visit(parser::ast::ASTVariableDeclStatementNode *node)=0;

        virtual void visit(parser::ast::ASTBlockStatementNode *node)=0;

        virtual void visit(parser::ast::ASTFunctionDeclStatementNode *node)=0;

        virtual void visit(parser::ast::ASTIfStatementNode *node)=0;

        virtual void visit(parser::ast::ASTWhileStatementNode *node)=0;

        virtual void visit(parser::ast::ASTPrintStatementNode *node)=0;

        virtual void visit(parser::ast::ASTReturnStatementNode *node)=0;

        virtual void visit(std::vector<std::unique_ptr<parser::ast::ASTNode>> &nodes);
    };
}


#endif //CPS2000_ASSIGNMENT_VISITOR_H
