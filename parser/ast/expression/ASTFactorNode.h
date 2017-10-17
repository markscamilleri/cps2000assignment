/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503.
 */

#ifndef CPS2000_ASSIGNMENT_ASTFACTORNODE_H
#define CPS2000_ASSIGNMENT_ASTFACTORNODE_H

#include "../ASTNode.h"

namespace parser {
    namespace ast {
        /**
         * Strongly typed factor type
         */
        enum FactorType {
            LITERAL,
            IDENTIFIER,
            FUNCTION_CALL,
            SUB_EXPRESSION,
            UNARY
        };

        /**
         * Class representing an abstract factor node in the AST
         */
        class ASTFactorNode : public ASTNode {
        public:
            /**
             * @return The type of factor this is. Use instead of checking the class type.
             */
            virtual FactorType getFactorType() = 0;

        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTFACTORNODE_H
