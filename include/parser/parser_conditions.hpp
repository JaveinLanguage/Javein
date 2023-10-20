#ifndef PARSER_CONDITIONS_H
#define PARSER_CONDITIONS_H

#include "../parser.hpp"

class ConditionsParser : public Parser
{
public:
    explicit ConditionsParser(const vector<Token> &tokens, int &currentIndex);
    void parseIfStatement();
    void parseConditional(const string& statementType);
};

#endif
