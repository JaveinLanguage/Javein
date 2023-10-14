#ifndef JAVEIN_PARSER_VARIABLES_HPP
#define JAVEIN_PARSER_VARIABLES_HPP

#include "../parser.hpp"

class VariablesParser : public Parser
{
public:
    explicit VariablesParser(const vector<Token> &tokens, size_t &currentTokenIndex);
    size_t parseVariableStatement();
};

#endif
