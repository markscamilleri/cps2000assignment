/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTEXPRNODE_H
#define CPS2000_ASSIGNMENT_ASTEXPRNODE_H


#include <memory>
#include "ASTNode.h"
#include "expression/ASTSimpleExprNode.h"

namespace parser {
    namespace ast {
        /**
         * @brief Enumerated type representing relational operators that can be used for an expression.
         */
        enum RelOpType {
            REL_GREATER,            ///< Greater than (<code>></code>) operator
            REL_GREATER_OR_EQUALS,  ///< Greater than or equals (<code>>=</code>) operator
            REL_EQUALS,             ///< Equals (<code>==</code>) operator
            REL_NOT_EQUALS,         ///< Not Equals (<code>!=</code>) operator
            REL_LESS_OR_EQUALS,     ///< Less than or equals (<code><=</code>) operator
            REL_LESS                ///< Less than (<code><</code> operator)
        };

        class ASTExprNode : public ASTNode {
        protected:
            /// The Simple Expression on the left hand side. This is mandatory
            std::unique_ptr<ASTSimpleExprNode> left;
            /// The Relational operator between the 2 simple expressions. Mandatory if the right hand side is not null
            RelOpType relationalOperator;
            /// The Simple Expression on the right hand side.  Optional
            std::unique_ptr<ASTSimpleExprNode> right;

        public:
            /**
             * Constructor for an expression with both sides of the relation operator
             * @param left The left hand side of this expression
             * @param relationalOperator The relational operator applied to this
             * @param right The right hand side of this expression
             */
            ASTExprNode(std::unique_ptr<ASTSimpleExprNode> left, RelOpType relationalOperator,
                        std::unique_ptr<ASTSimpleExprNode> right);

            /**
             * Constructor for when an expression does not have a relational operator
             * @param left The simple expression this expression is made of.
             */
            ASTExprNode(std::unique_ptr<ASTSimpleExprNode> left);

            /**
             * @return The left hand side of this expression
             */
            const std::unique_ptr<ASTSimpleExprNode> &getLeft() const;

            /**
             * @return The relation operator used in this expression
             *         NULL if there is no right hand side
             */
            RelOpType getRelationalOperator() const;

            /**
             * @return A pointer to the right hand side of this expression
             *         A pointer is returned as this is optional.
             */
            const std::unique_ptr<ASTSimpleExprNode> &getRight() const;

            /**
             * @param The relation operator to convert to a string
             * @return The string for the relational operator
             */
            const std::string getRelOpString() const;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTEXPRNODE_H
