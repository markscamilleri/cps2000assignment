/**
 * @file
 * @author Mark Said Camilleri <mark.said-camilleri.15@um.edu.mt>
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTWHILESTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTWHILESTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace parser {
    namespace ast {
        /**
         * This class represents a while statement node in the AST for the Minilang language
         */
        class ASTWhileStatementNode : public ASTStatementNode {
        protected:
            /// The predicate to be satisfied for the loop to keep executing
            std::unique_ptr<ASTExprNode> predicate;
            /// The block to be executed in the while loop
            std::unique_ptr<ASTBlockStatementNode> loopBlock;

        public:
            /**
             * The constructor for this object
             * @param predicate The predicate that needs to be satsified to keep looping
             * @param loopBlock  The block to be executed in the while loop (while the predicate holds)
             */
            ASTWhileStatementNode(std::unique_ptr<ASTExprNode> predicate,
                                  std::unique_ptr<ASTBlockStatementNode> loopBlock);

            /**
             * @return the predicate that needs to be satsified to keep looping
             */
            std::unique_ptr<ASTExprNode> & getPredicate();

            /**
             * @return the block to be executed in the while loop (while the predicate holds)
             */
            std::unique_ptr<ASTBlockStatementNode> & getLoopBlock();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;

        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTWHILESTATEMENTNODE_H
