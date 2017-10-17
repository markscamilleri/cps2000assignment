/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503
 */

#ifndef CPS2000_ASSIGNMENT_ASTTERMNODE_H
#define CPS2000_ASSIGNMENT_ASTTERMNODE_H

#include <memory>
#include "ASTFactorNode.h"
#include "../ASTNode.h"

namespace parser {
    namespace ast {

        /**
         *  Strong type for the multiplicative operator
         */
        enum MultiplicativeOp {
            MULTIPLICATION,
            DIVISION,
            AND
        };

        /**
         * Class representing a Term node in the AST
         */
        class ASTTermNode : public ASTNode{
        protected:
            /// The left hand side factor of this term
            std::unique_ptr<ASTFactorNode> left;

            /// The multiplicative operator of this term. Mandatory if right is not null.
            MultiplicativeOp op;

            /// The right hand side factor of this term
            std::unique_ptr<ASTFactorNode> right;

        public:
            /**
             * Constructor when this Term has 2 factors (left hand side and right hand side)
             * @param left The left hand side of this term
             * @param op The multiplicative operator to apply between the factors
             * @param right The right hand side of this term
             */
            ASTTermNode(std::unique_ptr<ASTFactorNode> left, MultiplicativeOp op,
                        std::unique_ptr<ASTFactorNode> right);

            /**
             * Constructor when this term has only 1 factor
             * @param left The factor of this term
             */
            ASTTermNode(std::unique_ptr<ASTFactorNode> left);

            /**
             * @return a reference to the pointer to the first factor
             */
            const std::unique_ptr<ASTFactorNode> &getLeft() const;

            /**
             * @return the operator that is applied to the factors
             */
            MultiplicativeOp getOp() const;

            /**
             * @return a reference to the pointer to the second, optional factor
             */
            const std::unique_ptr<ASTFactorNode> &getRight() const;


            const std::string getMutliplicativeOpString() const;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTTERMNODE_H
