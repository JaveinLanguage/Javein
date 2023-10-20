#ifndef JAVEIN_PARSER_CLASSES_HPP
#define JAVEIN_PARSER_CLASSES_HPP

#include "../parser.hpp"

class ClassesParser : public Parser
{
public:
    explicit ClassesParser(const vector<Token> &tokens, int &currentIndex);
    void parseClassStatement();
};

#endif
