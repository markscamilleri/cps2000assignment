//
// Created by mark on 13/03/17.
//

#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "../exceptions/SyntaxError.h"

lexer::Lexer::Lexer(std::vector<std::string> &file_contents) : file_contents(file_contents) {}


/**
 * A tail recursive approach was taken to avoid accessing memory after the end of the vector
 * @return The next token
 * @throws SyntaxError if the lexer is unable to parse the next token.
 */
lexer::Token lexer::Lexer::nextToken() {
    // A base case for the error
    if (pos.line == file_contents.end()) return Token(TOK_EOF, "EOF");

    // Discards lone whitespaces that are not tokenisable
    // A recursive case
    if (*(pos.character) == '\n' || *(pos.character) == ' ' || *(pos.character) == '\t') {
        goToNextCharacter();
        pos.chars_read = "";
        return nextToken();
    }

    // Variables for tokenisation process
    int currentState = 0; // sets currentState to the start state;
    int lastFinalState = currentState;
    std::vector<std::string>::iterator finalStateLine = pos.line;

    // Runs the string through the DFA
    std::string::iterator firstChar = pos.character;
    pos.chars_read = "";

    while (currentState != ERR) {
        if (currentState == 18) { // If token is of multiline comment ignore any form of whitespace
            while (isspace(*(pos.character))) goToNextCharacter();
        } else if (currentState == 19) { // If current state is that of single line comment, ignore spaces
            while (*(pos.character) == ' ' || *(pos.character) == '\t') goToNextCharacter();
        }

        currentState = transitionDFA(currentState, *(pos.character));

        // If it is a final state
        if (finalStateTokens.find(currentState) != finalStateTokens.end()) {
            lastFinalState = currentState;
        } else if (currentState == ERR) {
            goToPreviousCharacter();
        }
        goToNextCharacter();
    }

    // Tokenisable string
    // This needs to be checked after checking whitespace
    std::unordered_map<int, lexer::TokenType>::const_iterator tok = finalStateTokens.find(lastFinalState);

    if (tok != finalStateTokens.end()) {
        TokenType toReturn = tok->second;
        if (toReturn == TOK_IDENTIFIER) toReturn = checkIfKeyword(std::string(firstChar, pos.character));

        if (toReturn == TOK_MULTI_LINE_COMMENT || toReturn == TOK_SINGLE_LINE_COMMENT) return nextToken();
        else if (lastFinalState != 0) return Token(toReturn, pos.chars_read);
    }
    throw exceptions::SyntaxError("Unable to find token for " + pos.chars_read, pos.line - file_contents.begin(),
                                  pos.character - pos.line->begin());

}

int lexer::Lexer::transitionDFA(const int state, const char character) {
    return transitionDFA(state, (int) character);
}

int lexer::Lexer::transitionDFA(const int state, const int character) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (ALPHABET_PREDICATES[i](character) && transitions[state][i] != ERR) return transitions[state][i];
    }

    return ERR;
}

void lexer::Lexer::goToNextCharacter() {
    pos.chars_read += *(pos.character);
    ++(pos.character);
    if ((pos.character == pos.line->end() || *(pos.character) == '\0')) {
        goToNextLine();
        if (pos.line != file_contents.end())
            pos.character = pos.line->begin();
    }
}

void lexer::Lexer::goToPreviousCharacter() {
    if (pos.character == pos.line->begin()) {
        goToPreviousLine();
        pos.character = pos.line->end();
    }
    pos.character--;
    pos.chars_read = pos.chars_read.substr(0, pos.chars_read.size() - 1);
}

void lexer::Lexer::goToNextLine() {
    if (pos.line != file_contents.end())
        pos.line++;
}

void lexer::Lexer::goToPreviousLine() {
    if (pos.line != file_contents.begin())
        pos.line--;
}

lexer::TokenType lexer::Lexer::checkIfKeyword(std::string identifier) {
    if (identifier == "true" || identifier == "false") return TOK_BOOL_LITERAL;
    else if (identifier == "and") return TOK_AND;
    else if (identifier == "or") return TOK_OR;
    else if (identifier == "not") return TOK_NOT;
    else if (identifier == "if") return TOK_IF;
    else if (identifier == "else") return TOK_ELSE;
    else if (identifier == "while") return TOK_WHILE;
    else if (identifier == "int" || identifier == "real" || identifier == "bool" || identifier == "string")
        return TOK_TYPE;
    else if (identifier == "set") return TOK_SET;
    else if (identifier == "var") return TOK_VAR;
    else if (identifier == "print") return TOK_PRINT;
    else if (identifier == "def") return TOK_DEF;
    else if (identifier == "return") return TOK_RETURN;
    else return TOK_IDENTIFIER;
}

std::pair<int, int> lexer::Lexer::getPosition() {
    return std::pair<int, int>(pos.line - file_contents.begin(),
                               pos.character - pos.line->begin());
}
