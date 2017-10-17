/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170429
 */

#ifndef CPS2000_ASSIGNMENT_ASTASSIGNMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTASSIGNMENTNODE_H

#include <string>
#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "../expression/factor/ASTIdentifierNode.h"

namespace parser {
    namespace ast {
        /**
         * An AST node representing an assignment statement
         */
        class ASTAssignmentNode : public ASTStatementNode {
        protected:
            /// The variable's identifier
            std::unique_ptr<ASTIdentifierNode> identifier;
            // The expression whose result is stored in the variable
            std::unique_ptr<ASTExprNode> expr;
        public:
            /**
             * The constructor for this class
             * @param identifier The identifier of the variable created by this statement
             * @param expr The expression Node
             */
            ASTAssignmentNode(std::unique_ptr<parser::ast::ASTIdentifierNode> identifier, std::unique_ptr<ASTExprNode> expr);

            /**
             * @return A reference to the identifier string
             */
            std::unique_ptr<ASTIdentifierNode> & getIdentifier();

            /**
             * @return A reference to the expression
             */
            std::unique_ptr<ASTExprNode> &getExpr();



            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}


#endif //CPS2000_ASSIGNMENT_ASTASSIGNMENTNODE_H
