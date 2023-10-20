#ifndef JAVEIN_PARSER_HPP
#define JAVEIN_PARSER_HPP

#include "lexer.hpp"

class Parser
{
public:
    explicit Parser(const vector<Token> &tokens, int &currentIndex);

    void parse();
    bool checkCurrentTokenType(TOKENS expectedType);
    void parseBlock(const string &blockType);
    void advance();

    const vector<Token> &tokens;
    int &currentTokenIndex;
};

#include "parser/parser_variables.hpp"
#include "parser/parser_conditions.hpp"
#include "parser/parser_loops.hpp"
#include "parser/parser_functions.hpp"
#include "parser/parser_classes.hpp"
#include "parser/parser_constructors.hpp"

#include "errors.hpp"

#endif