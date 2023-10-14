#ifndef JAVEIN_PARSER_FUNCTIONS_HPP
#define JAVEIN_PARSER_FUNCTIONS_HPP

#include "../parser.hpp"

class FunctionsParser : public parser
{
public:
    explicit FunctionsParser(const vector<Token>& tokens, size_t currentTokenIndex);
    size_t parseFunction();
};


#endif
