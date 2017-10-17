//
// Created by mark on 13/03/17.
//

#ifndef CPS2000_ASSIGNMENT_ASTNODE_H
#define CPS2000_ASSIGNMENT_ASTNODE_H

#include <string>

namespace visitor{
    class Visitor;
}

namespace parser {
    namespace ast {
        class ASTNode {
        public:

            /**
             * Accepts a visitor and calls the operation by invoking <code>visit(this)</code>
             * @param visitor the visitor to accept
             */
            virtual void accept(visitor::Visitor *visitor)=0;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTNODE_H
