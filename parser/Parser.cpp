//
// Created by mark on 13/03/17.
//

#include <cstring>
#include <iostream>
#include "Parser.h"
#include "../exceptions/Exception.h"
#include "../exceptions/SyntaxError.h"

std::unique_ptr<parser::ast::ASTExprNode> parser::Parser::parseExpression() {
    std::unique_ptr<ast::ASTExprNode> expr;

    std::unique_ptr<ast::ASTSimpleExprNode> left = parseSimpleExpression();

    ast::RelOpType relOp;

    if (currentToken.getToken() == lexer::TOK_RELATIONAL_OP) {
        if (currentToken.getAttribute() == "<") {
            relOp = ast::RelOpType::REL_LESS;
        } else if (currentToken.getAttribute() == "<=") {
            relOp = ast::RelOpType::REL_LESS_OR_EQUALS;
        } else if (currentToken.getAttribute() == "==") {
            relOp = ast::RelOpType::REL_EQUALS;
        } else if (currentToken.getAttribute() == "!=") {
            relOp = ast::RelOpType::REL_NOT_EQUALS;
        } else if (currentToken.getAttribute() == ">=") {
            relOp = ast::RelOpType::REL_GREATER_OR_EQUALS;
        } else if (currentToken.getAttribute() == ">") {
            relOp = ast::RelOpType::REL_GREATER;
        } else {
            throw exceptions::SyntaxError("Expected < <= == != >= or >", lex.getPosition().first,
                                          lex.getPosition().second);
        }

        moveToNextToken();

        std::unique_ptr<ast::ASTSimpleExprNode> right = std::move(parseSimpleExpression());
        expr.reset(new ast::ASTExprNode(std::move(left), relOp, std::move(right)));

    } else {
        expr.reset(new ast::ASTExprNode(std::move(left)));
    }
    return std::move(expr);

}

std::unique_ptr<parser::ast::ASTStatementNode> parser::Parser::parseStatement() {
    switch (currentToken.getToken()) {
        case lexer::TOK_IF:
            return parseIfStatement();
        case lexer::TOK_WHILE:
            return parseWhileStatement();
        case lexer::TOK_SET:
            return parseAssignmentNode();
        case lexer::TOK_VAR:
            return parseVariableDeclaration();
        case lexer::TOK_PRINT:
            return parsePrintStatement();
        case lexer::TOK_DEF:
            return parseFunctionDeclaration();
        case lexer::TOK_RETURN:
            return parseReturnStatement();
        default:
            throw exceptions::SyntaxError("Expected a statement", lex.getPosition().first, lex.getPosition().second);
    }
}

std::unique_ptr<parser::ast::ASTSimpleExprNode> parser::Parser::parseSimpleExpression() {
    std::unique_ptr<ast::ASTSimpleExprNode> simpleExpr;

    std::unique_ptr<ast::ASTTermNode> left = parseTerm();

    ast::AdditiveOp addOp;
    switch (currentToken.getToken()) {
        case lexer::TokenType::TOK_ADDITION:
            addOp = ast::AdditiveOp::PLUS;
            break;
        case lexer::TokenType::TOK_SUBTRACTION:
            addOp = ast::AdditiveOp::MINUS;
            break;
        case lexer::TokenType::TOK_OR:
            addOp = ast::AdditiveOp::OR;
            break;
        default:
            simpleExpr.reset(new ast::ASTSimpleExprNode(std::move(left)));
            return std::move(simpleExpr);
    }

    // This continues if there's an operator, there is a right hand side simpleExpr
    moveToNextToken();

    std::unique_ptr<ast::ASTTermNode> right = parseTerm();
    simpleExpr.reset(new ast::ASTSimpleExprNode(std::move(left), addOp, std::move(right)));

    return std::move(simpleExpr);
}

std::unique_ptr<parser::ast::ASTTermNode> parser::Parser::parseTerm() {

    std::unique_ptr<ast::ASTTermNode> term;

    std::unique_ptr<ast::ASTFactorNode> left = parseFactor();

    ast::MultiplicativeOp multOp;
    switch (currentToken.getToken()) {
        case lexer::TokenType::TOK_MULTIPLICATION:
            multOp = ast::MultiplicativeOp::MULTIPLICATION;
            break;
        case lexer::TokenType::TOK_DIVISION:
            multOp = ast::MultiplicativeOp::DIVISION;
            break;
        case lexer::TokenType::TOK_AND:
            multOp = ast::MultiplicativeOp::AND;
            break;
        default:
            term.reset(new ast::ASTTermNode(std::move(left)));
            return std::move(term);
    }

    // This continues if there's an operator, there is a right hand side term
    moveToNextToken();

    std::unique_ptr<ast::ASTFactorNode> right = parseFactor();
    term.reset(new ast::ASTTermNode(std::move(left), multOp, std::move(right)));

    return std::move(term);
}

std::unique_ptr<parser::ast::ASTFactorNode> parser::Parser::parseFactor() {
    switch (currentToken.getToken()) {
        case lexer::TokenType::TOK_INTEGER_LITERAL:
        case lexer::TokenType::TOK_REAL_LITERAL:
        case lexer::TokenType::TOK_STRING_LITERAL:
        case lexer::TokenType::TOK_BOOL_LITERAL:
            return parseLiteral();
        case lexer::TokenType::TOK_NOT:
        case lexer::TokenType::TOK_SUBTRACTION:
            return parseUnaryNode();
        case lexer::TokenType::TOK_IDENTIFIER: {
            std::unique_ptr<ast::ASTIdentifierNode> identifier = parseIdentifier();
            if (currentToken.getToken() == lexer::TokenType::TOK_PUNCTUATION &&
                currentToken.getAttribute().find('(') != std::string::npos) {
                return parseFunctionCall(std::move(identifier));
            } else {
                return std::move(identifier);
            }
        }
        case lexer::TokenType::TOK_PUNCTUATION:
            if (currentToken.getAttribute().find('(') != std::string::npos) {
                return parseSubExpression();
            }
        default:
            throw exceptions::SyntaxError("Expected a factor", lex.getPosition().first, lex.getPosition().second);
    }
}

std::unique_ptr<parser::ast::ASTFunctionCallNode>
parser::Parser::parseFunctionCall(std::unique_ptr<ast::ASTIdentifierNode> identifier) {
    std::unique_ptr<ast::ASTFunctionCallNode> fnCall;

    checkPunctuationToken(currentToken, '(');

    std::vector<std::unique_ptr<ast::ASTExprNode>> params;

    moveToNextToken();

    if (currentToken.getToken() != lexer::TokenType::TOK_PUNCTUATION) {
        std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

        params.push_back(std::move(expr));
    }

    while (currentToken.getAttribute().find(')') == std::string::npos) {

        checkPunctuationToken(currentToken, ',');
        moveToNextToken();

        std::unique_ptr<ast::ASTExprNode> expr = parseExpression();
        params.push_back(std::move(expr));
    }

    checkPunctuationToken(currentToken, ')');
    moveToNextToken();

    fnCall.reset(new ast::ASTFunctionCallNode(std::move(identifier), params));

    return std::move(fnCall);
}

std::unique_ptr<parser::ast::ASTIdentifierNode> parser::Parser::parseIdentifier() {
    std::unique_ptr<ast::ASTIdentifierNode> identifier(new ast::ASTIdentifierNode(currentToken.getAttribute()));
    moveToNextToken();

    return std::move(identifier);
}

std::unique_ptr<parser::ast::ASTFactorNode> parser::Parser::parseLiteral() {
    std::unique_ptr<ast::ASTFactorNode> literal;

    switch (currentToken.getToken()) {
        case lexer::TokenType::TOK_INTEGER_LITERAL:
            literal.reset(new ast::ASTLiteralNode<int>(std::stoi(currentToken.getAttribute())));
            break;
        case lexer::TokenType::TOK_REAL_LITERAL:
            literal.reset(new ast::ASTLiteralNode<float>(std::stof(currentToken.getAttribute())));
            break;
        case lexer::TokenType::TOK_BOOL_LITERAL:
            literal.reset(new ast::ASTLiteralNode<bool>(currentToken.getAttribute() == "true"));
            break;
        case lexer::TokenType::TOK_STRING_LITERAL: {
            std::string value = currentToken.getAttribute();
            literal.reset(new ast::ASTLiteralNode<std::string>(value.substr(1, value.size() - 2)));
            break;
        }
        default:
            throw exceptions::SyntaxError("Expecting a literal", lex.getPosition().first, lex.getPosition().second);
    }

    moveToNextToken();
    return std::move(literal);
}

std::unique_ptr<parser::ast::ASTSubExpression> parser::Parser::parseSubExpression() {

    checkPunctuationToken(currentToken, '(');

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    moveToNextToken();
    checkPunctuationToken(currentToken, ')');

    std::unique_ptr<ast::ASTSubExpression> subExpr(new ast::ASTSubExpression(std::move(expr)));
    return std::move(subExpr);
}

std::unique_ptr<parser::ast::ASTUnaryNode> parser::Parser::parseUnaryNode() {
    ast::UnaryOperator unaryOperator;
    if (currentToken.getToken() == lexer::TokenType::TOK_SUBTRACTION) {
        unaryOperator = ast::UnaryOperator::NEGATIVE;
    } else if (currentToken.getToken() == lexer::TokenType::TOK_NOT) {
        unaryOperator = ast::UnaryOperator::NOT;
    } else {
        throw exceptions::SyntaxError("Expected '-' or 'not'", lex.getPosition().first, lex.getPosition().second);
    }

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    std::unique_ptr<ast::ASTUnaryNode> unary(new ast::ASTUnaryNode(unaryOperator, std::move(expr)));

    return std::move(unary);
}

std::unique_ptr<parser::ast::ASTAssignmentNode> parser::Parser::parseAssignmentNode() {
    moveToNextToken();
    std::unique_ptr<ast::ASTIdentifierNode> identifier = parseIdentifier();

    if (currentToken.getToken() != lexer::TokenType::TOK_ASSIGNMENT_EQUALS) {
        throw exceptions::SyntaxError("Expected '=' here", lex.getPosition().first, lex.getPosition().second);
    }

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    std::unique_ptr<ast::ASTAssignmentNode> assignment(
            new ast::ASTAssignmentNode(std::move(identifier), std::move(expr)));
    return std::move(assignment);
}

std::unique_ptr<parser::ast::ASTBlockStatementNode> parser::Parser::parseBlockStatement() {
    checkPunctuationToken(currentToken, '{');

    std::vector<std::unique_ptr<parser::ast::ASTStatementNode>> blockContents;

    moveToNextToken();

    while (currentToken.getAttribute().find('}') == std::string::npos) {
        std::unique_ptr<ast::ASTStatementNode> statement = parseStatement();

        blockContents.push_back(std::move(statement));

        moveToNextToken();
    }

    checkPunctuationToken(currentToken, '}');

    std::unique_ptr<ast::ASTBlockStatementNode> block(new ast::ASTBlockStatementNode(blockContents));
    return std::move(block);
}

std::unique_ptr<parser::ast::ASTFunctionDeclStatementNode> parser::Parser::parseFunctionDeclaration() {
    moveToNextToken();
    if (currentToken.getToken() != lexer::TokenType::TOK_IDENTIFIER) {
        throw exceptions::SyntaxError("Expected an identifier", lex.getPosition().first,
                                      lex.getPosition().second);
    }

    std::unique_ptr<ast::ASTIdentifierNode> identifier = parseIdentifier();

    checkPunctuationToken(currentToken, '(');

    std::vector<std::pair<std::unique_ptr<ast::ASTIdentifierNode>, ast::VariableType>> params;

    moveToNextToken();

    if (currentToken.getToken() != lexer::TokenType::TOK_PUNCTUATION) {
        auxParseArgDecl(params);
    }

    while (currentToken.getAttribute().find(')') == std::string::npos) {

        checkPunctuationToken(currentToken, ',');
        moveToNextToken();

        auxParseArgDecl(params);
    }

    checkPunctuationToken(currentToken, ')');

    moveToNextToken();
    checkPunctuationToken(currentToken, ':');

    moveToNextToken();
    ast::VariableType returnType = getVariableType();

    moveToNextToken();
    std::unique_ptr<ast::ASTBlockStatementNode> block = parseBlockStatement();

    std::unique_ptr<ast::ASTFunctionDeclStatementNode> node(
            new ast::ASTFunctionDeclStatementNode(std::move(identifier), params, returnType, std::move(block)));
    return std::move(node);
}

std::unique_ptr<parser::ast::ASTIfStatementNode> parser::Parser::parseIfStatement() {
    std::unique_ptr<ast::ASTIfStatementNode> node;

    moveToNextToken();
    checkPunctuationToken(currentToken, '(');

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> predicate = parseExpression();

    checkPunctuationToken(currentToken, ')');

    moveToNextToken();
    std::unique_ptr<ast::ASTBlockStatementNode> blockIfTrue = parseBlockStatement();
    moveToNextToken();
    if (currentToken.getToken() == lexer::TokenType::TOK_ELSE) {
        moveToNextToken();
        std::unique_ptr<ast::ASTBlockStatementNode> blockIfFalse = parseBlockStatement();

        node.reset(new ast::ASTIfStatementNode(std::move(predicate), std::move(blockIfTrue), std::move(blockIfFalse)));
    } else {
        node.reset(new ast::ASTIfStatementNode(std::move(predicate), std::move(blockIfTrue)));
    }

    return std::move(node);
}

std::unique_ptr<parser::ast::ASTPrintStatementNode> parser::Parser::parsePrintStatement() {
    moveToNextToken();

    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    std::unique_ptr<ast::ASTPrintStatementNode> node(new ast::ASTPrintStatementNode(std::move(expr)));

    return std::move(node);
}

std::unique_ptr<parser::ast::ASTReturnStatementNode> parser::Parser::parseReturnStatement() {
    moveToNextToken();

    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    std::unique_ptr<ast::ASTReturnStatementNode> node(new ast::ASTReturnStatementNode(std::move(expr)));

    return std::move(node);
}

std::unique_ptr<parser::ast::ASTVariableDeclStatementNode> parser::Parser::parseVariableDeclaration() {
    moveToNextToken();
    if (currentToken.getToken() != lexer::TokenType::TOK_IDENTIFIER) {
        throw exceptions::SyntaxError("Expected an identifier", lex.getPosition().first, lex.getPosition().second);
    }

    std::unique_ptr<ast::ASTIdentifierNode> identifier = parseIdentifier();

    checkPunctuationToken(currentToken, ':');

    moveToNextToken();

    if (currentToken.getToken() != lexer::TokenType::TOK_TYPE) {
        throw exceptions::SyntaxError("Expected the variable type", lex.getPosition().first, lex.getPosition().second);
    }

    ast::VariableType type = getVariableType();

    moveToNextToken();
    if (currentToken.getToken() != lexer::TokenType::TOK_ASSIGNMENT_EQUALS) {
        throw exceptions::SyntaxError("Expected '=' here", lex.getPosition().first, lex.getPosition().second);
    }

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> expr = parseExpression();

    std::unique_ptr<ast::ASTVariableDeclStatementNode> node(
            new ast::ASTVariableDeclStatementNode(std::move(identifier), type, std::move(expr)));

    return std::move(node);
}

std::unique_ptr<parser::ast::ASTWhileStatementNode> parser::Parser::parseWhileStatement() {
    moveToNextToken();
    checkPunctuationToken(currentToken, '(');

    moveToNextToken();
    std::unique_ptr<ast::ASTExprNode> predicate = parseExpression();

    checkPunctuationToken(currentToken, ')');

    moveToNextToken();
    std::unique_ptr<ast::ASTBlockStatementNode> block = parseBlockStatement();

    std::unique_ptr<ast::ASTWhileStatementNode> node(
            new ast::ASTWhileStatementNode(std::move(predicate), std::move(block)));
    return std::move(node);

}

parser::ast::VariableType parser::Parser::getVariableType() {
    parser::ast::VariableType type;
    if (currentToken.getAttribute() == "int") {
        type = parser::ast::INTEGER;
    } else if (this->currentToken.getAttribute() == "real") {
        type = parser::ast::REAL;
    } else if (this->currentToken.getAttribute() == "bool") {
        type = parser::ast::BOOLEAN;
    } else if (this->currentToken.getAttribute() == "string") {
        type = parser::ast::STRING;
    } else {
        throw exceptions::SyntaxError("Expected a variable type of int, real, bool or string", lex.getPosition().first,
                                      lex.getPosition().second);
    }
    return type;
}

void parser::Parser::checkPunctuationToken(lexer::Token tok, char punctuation) {
    if (currentToken.getToken() != lexer::TokenType::TOK_PUNCTUATION ||
        currentToken.getAttribute().find(punctuation) == std::string::npos) {
        std::string message = "Expected a '" + std::string(1, punctuation) + "'";
        throw exceptions::SyntaxError(message, lex.getPosition().first, lex.getPosition().second);
    }
}

void parser::Parser::moveToNextToken() {
    currentToken = nextToken;
    nextToken = lex.nextToken();
}

void parser::Parser::auxParseArgDecl(
        std::vector<std::pair<std::unique_ptr<ast::ASTIdentifierNode>, ast::VariableType>> &params) {
    if (currentToken.getToken() != lexer::TokenType::TOK_IDENTIFIER) {
        throw exceptions::SyntaxError("Expected an identifier", lex.getPosition().first, lex.getPosition().second);
    }

    std::unique_ptr<ast::ASTIdentifierNode> variableIdentifier(new ast::ASTIdentifierNode(
            currentToken.getAttribute()));

    moveToNextToken();
    checkPunctuationToken(currentToken, ':');

    moveToNextToken();
    if (currentToken.getToken() != lexer::TokenType::TOK_TYPE) {
        throw exceptions::SyntaxError("Expected the argument type", lex.getPosition().first,
                                      lex.getPosition().second);
    }

    ast::VariableType type = getVariableType();

    std::pair<std::unique_ptr<ast::ASTIdentifierNode>, ast::VariableType> parameter(std::move(variableIdentifier),
                                                                                    type);
    params.push_back(std::move(parameter));

    moveToNextToken();
}

std::vector<std::unique_ptr<parser::ast::ASTNode>> parser::Parser::parse() {
    std::vector<std::unique_ptr<ast::ASTNode>> nodes;

    while (currentToken.getToken() != lexer::TokenType::TOK_EOF) {
        nodes.push_back(parseStatement());
        moveToNextToken();
    }

    return nodes;
}

parser::Parser::Parser(std::vector<std::string> &lines) : lex(lexer::Lexer(lines)), currentToken(lex.nextToken()),
                                                          nextToken(lex.nextToken()) {}