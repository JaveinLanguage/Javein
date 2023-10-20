#include "../../include/parser/parser_loops.hpp"

LoopsParser::LoopsParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void LoopsParser::parseForStatement()
{
    if (!checkCurrentTokenType(TOKENS::FOR)) {
        return;
    }

    cout << "Parsing FOR Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after FOR statement" << endl;
        return;
    }

    advance();

    cout << "  Parsing Declaration:" << endl;

    if (!checkCurrentTokenType(TOKENS::INT_TYPE)) {
        cerr << "Error: Expected int type in the loop initialization" << endl;
        return;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        cerr << "Error: Expected identifier for loop variable" << endl;
        return;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ASSIGN)) {
        cerr << "Error: Expected '=' in the loop initialization" << endl;
        return;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::INT)) {
        cerr << "Error: Expected integer literal for loop initial value" << endl;
        return;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::SEMICOLON)) {
        cerr << "Error: Expected ';' after loop condition" << endl;
        return;
    }

    advance();

    cout << "  Parsing Condition:" << endl;

    while (!checkCurrentTokenType(TOKENS::SEMICOLON) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::SEMICOLON)) {
        cerr << "Error: Expected ';' after loop condition" << endl;
        return;
    }
    advance();

    cout << "  Parsing Increment:" << endl;

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
        cerr << "Error: Expected ')' after FOR statement" << endl;
        return;
    }

    parseBlock("FOR");
}

void LoopsParser::parseWhileStatement()
{
    if (!checkCurrentTokenType(TOKENS::WHILE)) {
        return;
    }

    cout << "Parsing WHILE Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after WHILE statement" << endl;
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

    parseBlock("WHILE");
}