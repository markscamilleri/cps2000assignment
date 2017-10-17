/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTFUNCTIONDECLSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTFUNCTIONDECLSTATEMENTNODE_H

#include <string>
#include <memory>
#include "../ASTStatementNode.h"
#include "ASTVariableDeclStatementNode.h"
#include "ASTBlockStatementNode.h"
#include "../expression/factor/ASTIdentifierNode.h"

namespace parser {
    namespace ast {
        /**
         * This class represents a function declaration statement in the AST
         */
        class ASTFunctionDeclStatementNode : public ASTStatementNode {
        protected:
            /// The function's name
            std::unique_ptr<ASTIdentifierNode> identifier;
            /// The function's parameters
            std::vector<std::pair<std::unique_ptr<ASTIdentifierNode>, VariableType>> formalParams;
            /// The return type
            VariableType returnType;
            /// The function block itself
            std::unique_ptr<ASTBlockStatementNode> block;

        public:
            /**
             * The constructor for this class
             * @param identifier  The fucntion name
             * @param params  The formal parameters of the function
             * @param returnType  The return type of the function
             * @param block  The function block
             */
            ASTFunctionDeclStatementNode(std::unique_ptr<ASTIdentifierNode> identifier,
                                         std::vector<std::pair<std::unique_ptr<parser::ast::ASTIdentifierNode>, VariableType>> &params,
                                         VariableType returnType, std::unique_ptr<ASTBlockStatementNode> block);

            /**
             * @return The function name
             */
            std::unique_ptr<ASTIdentifierNode> &getIdentifier();

            /**
             * @return The function parameters
             */
            std::vector<std::pair<std::unique_ptr<ASTIdentifierNode>, VariableType>> & getFormalParams();

            /**
             * @return The function return type
             */
            VariableType getReturnType();

            /**
             * @return The function block
             */
            std::unique_ptr<ASTBlockStatementNode> &getBlock();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTFUNCTIONDECLSTATEMENTNODE_H
