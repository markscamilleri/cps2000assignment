/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H
#define CPS2000_ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H

#include <memory>
#include "../ASTStatementNode.h"

namespace parser {
    namespace ast {

        class ASTBlockStatementNode: public ASTStatementNode {
        public:
            /**
             * @brief The contents of this block
             * @details This has a public visibility since ASTBlockStatementNode is really a wrapper.
             *          A <code>typedef</code> wasn't used due to the inheritance scheme for this class.
             */
            std::vector<std::unique_ptr<ASTStatementNode>> blockContents;

            /// Default constructor, with an empty block
            ASTBlockStatementNode();

            /**
             * Constructor for known block
             * @param blockContents The statements in this block.
             */
            ASTBlockStatementNode(std::vector<std::unique_ptr<ASTStatementNode>> &contents);

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H
