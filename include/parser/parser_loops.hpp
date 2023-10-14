#ifndef JAVEIN_PARSER_LOOPS_H
#define JAVEIN_PARSER_LOOPS_H

#include "../parser.hpp"

class LoopsParser : public Parser
{
public:
    explicit LoopsParser(const vector<Token> &tokens, size_t &currentTokenIndex);
    size_t parseForStatement();
    size_t parseWhileStatement();
};

#endif
