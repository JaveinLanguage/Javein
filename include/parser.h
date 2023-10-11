#ifndef JAVEIN_PARSER_H
#define JAVEIN_PARSER_H

#include "lexer.h"

class Parser
{
public:
    explicit Parser(const vector<Token>& tokens);

    void parse();

private:
    void parseStatement();
    void parseIfStatement();
    void parseWhileStatement();
    void parseForStatement();
    void parseFunctionDeclaration();
    void parseReturnStatement();

    bool match(TOKENS expected);

private:
    const vector<Token>& tokens;
    size_t currentPos;
};

#endif
