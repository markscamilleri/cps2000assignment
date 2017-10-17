/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTPRINTSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTPRINTSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"

namespace parser {
    namespace ast {
        /**
         * This class represents a print statement node in the AST
         */
        class ASTPrintStatementNode : public ASTStatementNode {
        protected:
            /// The expression whose result will be printed
            std::unique_ptr<ASTExprNode> expr;
        public:
            /**
             * The constructor of this class
             * @param expr The expression whose result will be printed
             */
            ASTPrintStatementNode(std::unique_ptr<ASTExprNode> expr);

            /**
             * @return The expression whose result will be printed
             */
            std::unique_ptr<ASTExprNode> & getExpr();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTPRINTSTATEMENTNODE_H
