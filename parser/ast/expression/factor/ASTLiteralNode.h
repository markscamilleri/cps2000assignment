/**
 * @file
  * @author Mark Said Camilleri
  * @version 20170503.
 */

#ifndef CPS2000_ASSIGNMENT_ASTLITERALNODE_H
#define CPS2000_ASSIGNMENT_ASTLITERALNODE_H

#include <string>
#include "../ASTFactorNode.h"
#include "../../ASTNode.h"

namespace parser {
    namespace ast {
        /**
         * Class representing a literal node in the AST
         */
        template<typename T>
        class ASTLiteralNode : public ASTFactorNode {
        protected:
            T literal;
        public:
            /**
             * Constructor for this literal
             * @param literal The literal to store
             */
            ASTLiteralNode(T literal);

            /**
             * @return the literal
             */
            T getLiteral() const;

            FactorType getFactorType() override;

            void accept(visitor::Visitor *visitor) override;
        };

        template
        class ASTLiteralNode<int>;

        template
        class ASTLiteralNode<float>;

        template
        class ASTLiteralNode<bool>;

        template
        class ASTLiteralNode<std::string>;
    }
}


#endif //CPS2000_ASSIGNMENT_ASTLITERALNODE_H
