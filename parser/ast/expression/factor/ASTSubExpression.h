/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170503.
 */

#ifndef CPS2000_ASSIGNMENT_ASTSUBEXPRESSION_H
#define CPS2000_ASSIGNMENT_ASTSUBEXPRESSION_H

#include "../ASTFactorNode.h"
#include "../../ASTExprNode.h"

namespace parser {
    namespace ast {
        /**
         * Class represneting a sub-expression in the AST
         */
        class ASTSubExpression: public ASTFactorNode {
        protected:

            /// The expression itself
            std::unique_ptr<ASTExprNode> expr;
        public:
            /**
             * Constructor for this sub-expression
             * @param expr pointer to the expression of this sub-expression
             */
            ASTSubExpression(std::unique_ptr<ASTExprNode> expr);

            /**
             * @return pointer to the expression of this sub-expression
             */
            const std::unique_ptr<ASTExprNode> &getExpr() const;

            FactorType getFactorType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTSUBEXPRESSION_H
