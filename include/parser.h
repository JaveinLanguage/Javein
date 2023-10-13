#ifndef JAVEIN_PARSER_H
#define JAVEIN_PARSER_H

#include "lexer.h"

class parser
{
public:
    explicit parser(const vector<Token>& tokens);

    void parse();
private:
    const vector<Token>& tokens;
    size_t currentTokenIndex;

    void parseIfStatement();
    void parseConditional(const string& statementType);

    void parseForStatement();
    void parseWhileStatement();

    void parseBlock(const string& blockType);
    bool checkCurrentTokenType(TOKENS expectedType);
    void advance();
};

#endif
