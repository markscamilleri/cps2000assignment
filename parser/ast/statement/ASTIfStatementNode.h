/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */
#ifndef CPS2000_ASSIGNMENT_ASTIFSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTIFSTATEMENTNODE_H

#include <vector>
#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace parser {
    namespace ast {
        /**
         * This class represents an "if else" statment in the AST
         * This would also represent an "if" statmement by not having an else block
         */
        class ASTIfStatementNode : public ASTStatementNode {
        protected:
            /// The condition of the if statement
            std::unique_ptr<ASTExprNode> predicate;
            /// The block to execute if the predicate holds
            std::unique_ptr<ASTBlockStatementNode> blockIfTrue;
            /// The block to execute if the predicate does not hold
            std::unique_ptr<ASTBlockStatementNode> blockIfFalse;
        public:
            /**
             * This is the constructor for an if-else statmeent
             * @param predicate The condition to the if statement
             * @param blockIfTrue The block to execute if the predicate holds
             * @param blockIfFalse The block to exiecute if the predicate does not hold
             */
            ASTIfStatementNode(std::unique_ptr<ASTExprNode> predicate,
                               std::unique_ptr<ASTBlockStatementNode> blockIfTrue,
                               std::unique_ptr<ASTBlockStatementNode> blockIfFalse);

            /**
             * This is the constructor for an if statmeent
             * @param predicate The condition to the if statement
             * @param blockIfTrue The block to execute if the predicate holds
             */
            ASTIfStatementNode(std::unique_ptr<ASTExprNode> predicate,
                               std::unique_ptr<ASTBlockStatementNode> blockIfTrue);

            /**
             * @return The predicate expression of the if statement
             */
            std::unique_ptr<ASTExprNode> & getPredicate();

            /**
             * @return The block to execute if the predicate holds
             */
            std::unique_ptr<ASTBlockStatementNode> & getBlockIfTrue();

            /**
             * @return The block to execute if the predicate does not hold
             */
            std::unique_ptr<ASTBlockStatementNode> & getBlockIfFalse();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTIFSTATEMENTNODE_H
