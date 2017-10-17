//
// Created by mark on 13/03/17.
//

#ifndef CPS2000_ASSIGNMENT_ASTSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTSTATEMENTNODE_H


#include <vector>
#include "ASTNode.h"

namespace parser {
    namespace ast {
        /**
         * Strongly typed statement type
         */
        enum StatementType{
            ASSIGNMENT,
            BLOCK_STATEMENT,
            FUNCTION_DECL,
            IF,
            PRINT,
            RETURN,
            VARIABLE_DECL,
            WHILE
        };

        class ASTStatementNode: public ASTNode {
        public:
            /**
             * Virtual Method to return the statement type
             * @return The statement type (instead of checking what class it's an instance of)
             */
            virtual StatementType getStatementType() = 0;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTSTATEMENTNODE_H
