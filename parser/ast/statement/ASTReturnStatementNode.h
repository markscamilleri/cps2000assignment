/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTRETURNSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTRETURNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"

namespace parser{
    namespace ast{
        /**
         * This class represents a node in the AST that represents a <code>return</code> statement.
         */
        class ASTReturnStatementNode: public ASTStatementNode {
        protected:
            /// The expression whose result will be returned
            std::unique_ptr<ASTExprNode> expr;

        public:
            /**
             * The constructor for this class
             * @param expr The expression whose result will be returned
             */
            ASTReturnStatementNode(std::unique_ptr<ASTExprNode> expr);

            /**
             * @return The expression whose result will be returned
             */
            std::unique_ptr<ASTExprNode> & getExpr();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTRETURNSTATEMENTNODE_H
