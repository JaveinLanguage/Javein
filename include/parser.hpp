#ifndef JAVEIN_PARSER_HPP
#define JAVEIN_PARSER_HPP

#include "lexer.hpp"

class parser
{
public:
    explicit parser(const vector<Token>& tokens, size_t currentTokenIndex);

    void setCurrentTokenIndex(const size_t index)
    {
        currentTokenIndex = index;
    }

    void parse();
    bool checkCurrentTokenType(TOKENS expectedType);
    void parseBlock(const string& blockType);
    void advance();

    const vector<Token>& tokens;
    size_t currentTokenIndex;
};

#include "parser/parser_conditions.hpp"
#include "parser/parser_loops.hpp"
#include "parser/parser_functions.hpp"

#endif