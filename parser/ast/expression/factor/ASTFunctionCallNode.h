/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170503.
 */

#ifndef CPS2000_ASSIGNMENT_ASTFUNCTIONCALLNODE_H
#define CPS2000_ASSIGNMENT_ASTFUNCTIONCALLNODE_H

#include <vector>
#include "../ASTFactorNode.h"
#include "ASTIdentifierNode.h"
#include "../../ASTExprNode.h"

namespace parser {
    namespace ast {
        class ASTFunctionCallNode : public ASTFactorNode {
        protected:
            /// The function name
            std::unique_ptr<ASTIdentifierNode> identifier;

            /// The parameters to be passed
            std::vector<std::unique_ptr<ASTExprNode>> actualParams;

        public:
            ASTFunctionCallNode(std::unique_ptr<ASTIdentifierNode> identifier,
                                std::vector<std::unique_ptr<ASTExprNode>> &actualParams);

            ASTFunctionCallNode(std::unique_ptr<ASTIdentifierNode> identifier);

            FactorType getFactorType() override;

            std::unique_ptr<ASTIdentifierNode> &getIdentifier();

            std::vector<std::unique_ptr<ASTExprNode>> &getActualParams();

            void accept(visitor::Visitor *visitor) override;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTFUNCTIONCALLNODE_H
