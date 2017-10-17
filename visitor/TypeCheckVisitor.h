/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170519.
 */

#ifndef CPS2000_ASSIGNMENT_TYPECHECKVISITOR_H
#define CPS2000_ASSIGNMENT_TYPECHECKVISITOR_H

#include <map>
#include "Visitor.h"
#include "helpers/ScopedSymbolTable.h"

#define RETURN_VAR "automated|return"

namespace visitor {

    class TypeCheckVisitor : public Visitor {
    private:
        /// This is the symbol table
        helper::ScopedSymbolTable symbolTable;

        /// Last type checked
        helper::SymbolType type;

        /**
         * Throws a TypeError if the types do not match
         * @param type1 first type to check
         * @param type2 second type to check
         */
        void assertTypeMatch(helper::SymbolType type1, helper::SymbolType type2);

        /**
         * Throws a TypeError if the types match
         * @param type1 first type to check
         * @param type2 second type to check
         */
        void assertTypeMismatch(helper::SymbolType type1, helper::SymbolType type2);

        /**
         * Throws a TypeError if:
         *        - operator is AND, type is not boolean
         *        - operator is MULTIPLICATION or DIVSION, type is either boolean or string
         * @param type type to check against
         * @param multiplicativeOp operator to check
         */
        void assertOperatorTypeMatch(helper::SymbolType type, parser::ast::MultiplicativeOp multiplicativeOp);

        /**
         * Throws a TypeError if:
         *        - operator is OR, type is not boolean
         *        - operator is ADDITION or SUBTRACTION, type is either boolean or string
         * @param type type to check against
         * @param additiveOp operator to check
         */
        void assertOperatorTypeMatch(helper::SymbolType type, parser::ast::AdditiveOp additiveOp);

        /**
         * Throws a TypeError if:
         *        - operator is NOT, type is not boolean
         *        - operator is NEGATIVE, type is either boolean or string
         * @param type type to check against
         * @param unaryOperator operator to check
         */
        void assertOperatorTypeMatch(helper::SymbolType type, parser::ast::UnaryOperator unaryOperator);

        /**
         * Throws a TypeError if the type given is not the same as the return type or
         * if "automated|return" is not defined in the symbol table. | is used as it is not
         * accepted by the language for an identifier. Thsi is better than storing a function return type as a field and
         * checking against that as this checks if the function should actually return that type (all functions must
         * return something).
         * @param type type to check
         */
        void assertReturnTypeMatch(helper::SymbolType type);

    public:
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
    };
}


#endif //CPS2000_ASSIGNMENT_TYPECHECKVISITOR_H
