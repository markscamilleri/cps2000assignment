/**
 * @file
 * @author Mark Said Camilleri <mark.said-camilleri.15@um.edu.mt>
 * @version 20170430
 */

#ifndef CPS2000_ASSIGNMENT_ASTVARIABLEDECLSTAMENT_H
#define CPS2000_ASSIGNMENT_ASTVARIABLEDECLSTAMENT_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "../expression/factor/ASTIdentifierNode.h"
#include <string>


namespace parser {
    namespace ast {
        /**
         * @brief An enumerated type to represent the variable type
         */

        enum VariableType  {
            INTEGER,    ///< An Integer (<code>int</code>) type
            REAL,   ///< A Real (<code>real</code>) type
            BOOLEAN,   ///< A Bool (<code>bool</code>) type
            STRING  ///< A String (<code>string</code>) type
        };

        /**
         * @param type the VariableType to convert to a string
         * @return the string representation of the Variable type given
         */
        static std::string getVariableTypeString(VariableType type){
            switch(type){
                case INTEGER:
                    return "INTEGER";
                case REAL:
                    return "REAL";
                case BOOLEAN:
                    return "BOOLEAN";
                case STRING:
                    return "STRING";
                default:
                    return "";
            }
        }

        /**
         * The ASTVariableDeclStatementNode represents an AST node for a Variable Decleration Sentential form in the
         * MiniLang Language
         */
        class ASTVariableDeclStatementNode : public ASTStatementNode {
        protected:
            /// The variable identifier
            std::unique_ptr<ASTIdentifierNode> identifier;
            /// The variable type
            VariableType type;
            /// The expression making up this variable
            std::unique_ptr<ASTExprNode> expr;

        public:
            /**
             * Consturctor when the expression node is already created.
             * @param identifier the variable identifier
             * @param type the variable type, can be one of
             *    - <code>VariableType::VAR_INT</code>
             *    - <code>VariableType::VAR_REAL</code>
             *    - <code>VariableType::VAR_BOOL</code>
             *    - <code>VariableType::VAR_STRING</code>
             * @param exp The Expression node that will make up this variable.
             */
            ASTVariableDeclStatementNode(std::unique_ptr<ASTIdentifierNode> identifier, VariableType type,
                                       std::unique_ptr<ASTExprNode> expr);

            /**
             * @return The variable identifier
             */
            std::unique_ptr<ASTIdentifierNode> & getIdentifier();

            /**
             * @return The variable type
             */
            VariableType getType() const;

            /**
             * @return The expression node to create this variable
             */
            std::unique_ptr<ASTExprNode> & getExpr();

            StatementType getStatementType() override;

            void accept(visitor::Visitor *visitor) override;
        };
    }
}

#endif //CPS2000_ASSIGNMENT_ASTVARIABLEDECLSTAMENT_H
