#ifndef PARSER_CONDITIONS_H
#define PARSER_CONDITIONS_H

#include "../parser.hpp"

class ConditionsParser : public parser
{
public:
    explicit ConditionsParser(const vector<Token>& tokens, size_t currentTokenIndex);
    size_t parseIfStatement();
    void parseConditional(const string& statementType);
};

#endif
