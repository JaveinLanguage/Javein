#ifndef JAVEIN_PARSER_CONSTRUCTORS_HPP
#define JAVEIN_PARSER_CONSTRUCTORS_HPP

#include "../parser.hpp"

class ConstructorParser : public Parser
{
public:
    explicit ConstructorParser(const vector<Token> &tokens, size_t &currentTokenIndex);
    size_t parseConstructor(const string &className);
private:
    bool hasConstructor(const string &className);
};

#endif
