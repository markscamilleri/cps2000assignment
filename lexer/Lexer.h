/**
 * @file
 * @author Mark Said Camilleri
 * @version 20170426
 */

#ifndef CPS2000_ASSIGNMENT_LEXER_H
#define CPS2000_ASSIGNMENT_LEXER_H

#ifndef ERR
#define ERR -99
#endif

#ifndef ALPHABET_SIZE
#define ALPHABET_SIZE 17
#endif

#ifndef NO_OF_STATES
#define NO_OF_STATES 22 /* 0 - 21 */
#endif

#ifndef TERMINAL_NODE
#define TERMINAL_NODE {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}
#endif

#include <array>
#include <vector>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include "TokenType.h"

namespace lexer {

    /**
     * This struct represents the cursor used to read the file input
     */
    typedef struct Position {
        std::vector<std::string>::iterator line;
        std::string::iterator character;
        std::string chars_read;
    } Position;

    /**
     * This lexer acts as a DFA
     * Note that this DFA is really an NFA, since the checks are those that are defined in ALPHABET_PREDICATES.
     * However, the order of these predicates is indeed a priority, starting from the highest to the lowest and as
     * a result, the Finite-State Automata will not return more than one state, thus making it a deterministic.
`    */
    class Lexer {
    private:
        /// The set of characters to consider as punctuation
        const std::unordered_set<int> punctuation = {',',':', ';', '(', '{', ')', '}'};

        /// The functions used for the DFA
        const std::array<std::function<int(int)>, ALPHABET_SIZE> ALPHABET_PREDICATES = {
                [](int c) { return isdigit(c); },
                [](int c) { return static_cast<int> (c == '.'); },
                [](int c) { return isalpha(c); },
                [](int c) { return static_cast<int> (c == '_'); },
                [](int c) { return static_cast<int> (c == '*'); },
                [](int c) { return static_cast<int> (c == '+'); },
                [](int c) { return static_cast<int> (c == '-'); },
                [](int c) { return static_cast<int> (c == '/'); },
                [](int c) { return static_cast<int> (c == '='); },
                [](int c) { return static_cast<int> (c == '<'); },
                [](int c) { return static_cast<int> (c == '>'); },
                [](int c) { return static_cast<int> (c == '!'); },
                [this](int c) {
                    return static_cast<int> (punctuation.count(c));
                },
                [](int c) { return static_cast<int> (c == '\n'); },
                [](int c) { return static_cast<int> (c == '\"'); },
                [](int c) { return isprint(c); },
                [](int c) { return isspace(c); }
        };

        /**
         * The DFA transitions, with the conditions used in <code>ALPHABET_PREDICATES</code>
         */
        const std::array<std::array<int, ALPHABET_SIZE>, NO_OF_STATES> transitions = {
                {
                        /* S0  */ {1, ERR, 4, 4, 5, 6, 7, 8, 13, 9, 9, 17, 21, ERR, 15, ERR, ERR},
                        /* S1  */ {1, 14, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S2  */ {2, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S3  */ TERMINAL_NODE,
                        /* S4  */ {4, ERR, 4, 4, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S5  */ TERMINAL_NODE,
                        /* S6  */ TERMINAL_NODE,
                        /* S7  */ TERMINAL_NODE,
                        /* S8  */ {ERR, ERR, ERR, ERR, 18, ERR, ERR, 19, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S9  */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S10 */ TERMINAL_NODE,
                        /* S11 */ TERMINAL_NODE,
                        /* S12 */ TERMINAL_NODE,
                        /* S13 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S14 */ {2, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S15 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 3, 16, 16},
                        /* S16 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 3, 16, 16},
                        /* S17 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
                        /* S18 */ {ERR, ERR, ERR, ERR, 20, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 18, 18},
                        /* S19 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 11, ERR, 19, 19},
                        /* S20 */ {ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 18, 18},
                        /* S21 */ TERMINAL_NODE,
                }
        };

        /**
         * Set of final states of the DFA
         */
        const std::unordered_map<int, lexer::TokenType> finalStateTokens = {{1,  TOK_INTEGER_LITERAL},
                                                                         {2,  TOK_REAL_LITERAL},
                                                                         {3,  TOK_STRING_LITERAL},
                                                                         {4,  TOK_IDENTIFIER},
                                                                         {5,  TOK_MULTIPLICATION},
                                                                         {6,  TOK_ADDITION},
                                                                         {7,  TOK_SUBTRACTION},
                                                                         {8,  TOK_DIVISION},
                                                                         {9,  TOK_RELATIONAL_OP},
                                                                         {10, TOK_RELATIONAL_OP},
                                                                         {11, TOK_SINGLE_LINE_COMMENT},
                                                                         {12, TOK_MULTI_LINE_COMMENT},
                                                                         {13, TOK_ASSIGNMENT_EQUALS},
                                                                         {21, TOK_PUNCTUATION}};

        /// The contents of the file input
        std::vector<std::string> file_contents;

        /// The cursor used to read <code>file_contents</code>
        Position pos = {file_contents.begin(), file_contents.begin()->begin(), ""};

        /**
         * Performs the transition function based on the character read and the current state
         * @param state The state the program is currently in
         * @param character The character to be read
         * @return The next state
         */
        int transitionDFA(const int state, const char character);

        /**
         * Performs the transition function based on the character read and the current state
         * @param state The state the program is currently in
         * @param character The character to be read
         * @return The next state
         */
        int transitionDFA(const int state, const int character);

        /// Moves the cursor <code>pos</code> to the next character, checking for end of line and end of file
        void goToNextCharacter();

        /// Moves the cursor <code>pos</code> to the previous character, checking for beginning of line and
        /// beginning of file
        void goToPreviousCharacter();

        /// Moves the cursor <code>pos</code> to the next line, checking for end of file
        void goToNextLine();

        /// Moves the cursor <code>pos</code> to the previous line, checking for beginning of file
        void goToPreviousLine();

        /**
         * If an identifer is found, it is then checked whether it is actually a keyword and returns the respective
         * token
         * @param identifier The identifier string to check
         * @return a Token from the following:
         *         - <code>TOK_AND</code>
         *         - <code>TOK_OR</code>
         *         - <code>TOK_NOT</code>
         *         - <code>TOK_IF</code>
         *         - <code>TOK_ELSE</code>
         *         - <code>TOK_WHILE</code>
         *         - <code>TOK_TYPE</code>
         *         - <code>TOK_SET</code>
         *         - <code>TOK_VAR</code>
         *         - <code>TOK_PRINT</code>
         *         - <code>TOK_DEF</code>
         *         - <code>TOK_RETURN</code>
         *         - <code>TOK_IDENTIFIER</code>
         */
        TokenType checkIfKeyword(std::string identifier);


    public:

        /**
         * Constructor with the file contents, useful for debugging purposes.
         * @param file_contents The vector with the contents of the file.
         */
        Lexer(std::vector<std::string> &file_contents);

        /**
         * Returns the next token that was found from the file contnets.
         * @return THe next Token to be parsed.
         */
        Token nextToken();

        /**
         * Returns the current cursor position
         * @return tuple containing integers as <row, col>
         */
        std::pair<int,int> getPosition();
    };
}  // namespace lexer
#endif  // CPS2000_ASSIGNMENT_LEXER_H
