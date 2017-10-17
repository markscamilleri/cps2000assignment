/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170505.
 */

#ifndef CPS2000_ASSIGNMENT_ASTUNARYNODE_H
#define CPS2000_ASSIGNMENT_ASTUNARYNODE_H

#include "../ASTFactorNode.h"
#include "../../ASTExprNode.h"

namespace parser {
    namespace ast {
        /**
         * Strongly typed unary operator
         */
        enum UnaryOperator{
            NEGATIVE,
            NOT
        };

        /**
         * Class that represents a unary expression in the AST
         */
        class ASTUnaryNode : public ASTFactorNode {
        protected:
            /// Operator to use for this Unary
            UnaryOperator op;

            /// Expression for this unary
            std::unique_ptr<ASTExprNode> expr;

        public:
            /**
             * Constructor to use for this class
             * @param op The operator
             * @param expr The expression it is applied on
             */
            ASTUnaryNode(UnaryOperator op, std::unique_ptr<ASTExprNode> expr);

            /**
             * @return the unary operator
             */
            UnaryOperator getOp() const;

            /**
             * @return the expression after the operator
             */
            const std::unique_ptr<ASTExprNode> &getExpr() const;

            /** Converts a Unary Operator to a string representation of it
             * @param op the operator to convert to a string
             * @return the string representation of that operator
             */
            const std::string getOpString() const;

            FactorType getFactorType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTUNARYNODE_H
