#ifndef JAVEIN_PARSER_FUNCTIONS_HPP
#define JAVEIN_PARSER_FUNCTIONS_HPP

#include "../parser.hpp"

class FunctionsParser : public Parser
{
public:
    explicit FunctionsParser(const vector<Token> &tokens, int &currentIndex);
    void parseFunction();
};


#endif
