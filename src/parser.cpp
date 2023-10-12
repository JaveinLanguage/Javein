#include "../include/parser.h"

parser::parser(const vector<Token> &tokens) : tokens(tokens), currentTokenIndex(0) {}

void parser::parse()
{
    while (currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::IF)) {
            parseIfStatement();
        }
    }
}

void parser::parseIfStatement()
{
    if (!checkCurrentTokenType(TOKENS::IF)) {
        return;
    }

    cout << "Parsing IF Statement:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after if statement" << endl;
        return;
    }

    advance();

    cout << "  Parsing Condition:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        cerr << "Error: Expected ')' after if statement" << endl;
        return;
    }

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_BRACK)) {
        cerr << "Error: Expected '{' after if statement" << endl;
        return;
    }

    advance();

    cout << "  Parsing Block:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_BRACK) && currentTokenIndex < tokens.size()) {
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_BRACK)) {
        cerr << "Error: Expected '}' after if statement" << endl;
        return;
    }

    advance();
}

bool parser::checkCurrentTokenType(TOKENS expectedType)
{
    return tokens[currentTokenIndex].type == expectedType;
}

void parser::advance()
{
    if (currentTokenIndex < tokens.size()) {
        currentTokenIndex++;
    }
}