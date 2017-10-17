/**
 * @file
* @author Mark Said Camilleri
* @version 20170503.
 */

#ifndef CPS2000_ASSIGNMENT_ASTIDENTIFIERNODE_H
#define CPS2000_ASSIGNMENT_ASTIDENTIFIERNODE_H

#include <string>
#include <memory>
#include "../ASTFactorNode.h"
#include "../../ASTNode.h"

namespace parser {
    namespace ast {
        class ASTIdentifierNode : public ASTFactorNode {
        protected:
            /// the identifier
            std::string name;

        public:
            /**
             * Construtor for this class
             * @param name the name of the identifier
             */
            ASTIdentifierNode(const std::string name);

            /**
             * @return The name of the identifier
             */
            const std::string getName() const;

            FactorType getFactorType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTIDENTIFIERNODE_H
