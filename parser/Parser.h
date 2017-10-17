//
// Created by mark on 13/03/17.
//

#ifndef CPS2000_ASSIGNMENT_PARSER_H
#define CPS2000_ASSIGNMENT_PARSER_H

#include <memory>
#include "ast/ASTNode.h"
#include "ast/ASTExprNode.h"
#include "ast/expression/factor/ASTFunctionCallNode.h"
#include "ast/expression/factor/ASTLiteralNode.h"
#include "ast/expression/factor/ASTSubExpression.h"
#include "ast/expression/factor/ASTUnaryNode.h"
#include "ast/statement/ASTAssignmentNode.h"
#include "ast/statement/ASTBlockStatementNode.h"
#include "ast/statement/ASTFunctionDeclStatementNode.h"
#include "ast/statement/ASTIfStatementNode.h"
#include "ast/statement/ASTPrintStatementNode.h"
#include "ast/statement/ASTReturnStatementNode.h"
#include "ast/statement/ASTWhileStatementNode.h"
#include "../lexer/TokenType.h"
#include "../lexer/Lexer.h"

namespace parser {
    class Parser {
    private:
        /// Lexer that is used for this parser
        lexer::Lexer lex;

        /// The token that is being parsed
        lexer::Token currentToken;

        /// The next token to be parsed;
        lexer::Token nextToken;

        std::unique_ptr<ast::ASTExprNode> parseExpression();

        std::unique_ptr<ast::ASTStatementNode> parseStatement();

        std::unique_ptr<ast::ASTSimpleExprNode> parseSimpleExpression();

        std::unique_ptr<ast::ASTTermNode> parseTerm();

        std::unique_ptr<ast::ASTFactorNode> parseFactor();

        std::unique_ptr<ast::ASTFunctionCallNode> parseFunctionCall(std::unique_ptr<ast::ASTIdentifierNode> identifier);

        std::unique_ptr<ast::ASTIdentifierNode> parseIdentifier();

        std::unique_ptr<ast::ASTFactorNode> parseLiteral();

        std::unique_ptr<ast::ASTSubExpression> parseSubExpression();

        std::unique_ptr<ast::ASTUnaryNode> parseUnaryNode();

        std::unique_ptr<ast::ASTAssignmentNode> parseAssignmentNode();

        std::unique_ptr<ast::ASTBlockStatementNode> parseBlockStatement();

        std::unique_ptr<ast::ASTFunctionDeclStatementNode> parseFunctionDeclaration();

        std::unique_ptr<ast::ASTIfStatementNode> parseIfStatement();

        std::unique_ptr<ast::ASTPrintStatementNode> parsePrintStatement();

        std::unique_ptr<ast::ASTReturnStatementNode> parseReturnStatement();

        std::unique_ptr<ast::ASTVariableDeclStatementNode> parseVariableDeclaration();

        std::unique_ptr<ast::ASTWhileStatementNode> parseWhileStatement();

        /**
         * Auxiliary function to parse parameter/argument declarations
         * @param params The vector to store the parsed parameter declaration in.
         */
        void
        auxParseArgDecl(std::vector<std::pair<std::unique_ptr<ast::ASTIdentifierNode>, ast::VariableType>> &params);

        /**
         * Throws a syntax error if the token given does not have the correct punctuation
         * @param tok The token to check
         * @param punctuation The punctuation character that it should be
         */
        void checkPunctuationToken(lexer::Token tok, char punctuation);

        /**
         * @return the variable type depending on the token attribute
         */
        ast::VariableType getVariableType();

        /**
         * Moves <code>nextToken</code> to <code>currentToken</code> and gets the next token
         */
        void moveToNextToken();


    public:

        Parser(std::vector<std::string> &lines);

        /**
         * @return a (sort of abstract) root node in the form of a vector of nodes
         */
        std::vector<std::unique_ptr<ast::ASTNode>> parse();

    };
}

#endif //CPS2000_ASSIGNMENT_PARSER_H