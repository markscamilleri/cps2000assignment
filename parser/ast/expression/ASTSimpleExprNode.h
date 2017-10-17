//
// Created by mark on 28/04/17.
//

#ifndef CPS2000_ASSIGNMENT_ASTSIMPLEEXPRNODE_H
#define CPS2000_ASSIGNMENT_ASTSIMPLEEXPRNODE_H

#include "ASTTermNode.h"
#include "../ASTNode.h"

namespace parser {
    namespace ast {
        /**
         * Strong type for additive operator
         */
        enum AdditiveOp {
            PLUS,
            MINUS,
            OR
        };

        /**
         * Class representing a simple expression in the AST
         */
        class ASTSimpleExprNode : public ASTNode {
        protected:

            /// The left hand term of this expression (mandatory)
            std::unique_ptr<ASTTermNode> left;

            /// The additive operator of this expression (mandatory if right hand side is present)
            AdditiveOp addOp;

            /// The right hand side of this expression (optional)
            std::unique_ptr<ASTTermNode> right;


        public:
            /**
             * Constructor for when the simple expression is only made up of the left hand side
             * @param left The left hand side term of this simple expression
             */
            ASTSimpleExprNode(std::unique_ptr<ASTTermNode> left);

            /**
             * Constructor for when the simple expression is made up of both sides
             * @param left  The left hand side term of this simple expression
             * @param addOp The additive operator for this simple expression. This can be one of:
             *        - <code>ADD</code>     : addition
             *        - <code>MINUS</code>   : subtraction
             *        - <code>OR</code>      : or
             * @param right The right hand side term of this simple expression.
             */
            ASTSimpleExprNode(std::unique_ptr<ASTTermNode> left, AdditiveOp addOp,
                              std::unique_ptr<ASTTermNode> right);


            /**
             * @return Pointer to the left hand side of the simple expression
             */
            std::unique_ptr<ASTTermNode> & getLeft();

            /**
             * @return Additive Operator type of this expression
             */
            AdditiveOp getAddOp();

            /**
             * @return Pointer to the right hand side of the simple expression
             */
            std::unique_ptr<ASTTermNode> & getRight();

            /**
             * @param adOp The additive operator to convert to a string
             * @return String representing the additive operator
             */
            std::string getAdditiveOperatorString();

            void accept(visitor::Visitor *visitor) override;

        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTSIMPLEEXPRNODE_H