#include "../../include/parser/parser_loops.hpp"

LoopsParser::LoopsParser(const vector<Token> &tokens, size_t &currentTokenIndex) : Parser(tokens, currentTokenIndex) {}

size_t LoopsParser::parseForStatement()
{
    if (!checkCurrentTokenType(TOKENS::FOR)) {
        return 0;
    }

    cout << "Parsing FOR Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after FOR statement" << endl;
        return 0;
    }

    advance();

    cout << "  Parsing Declaration:" << endl;

    if (!checkCurrentTokenType(TOKENS::INT_TYPE)) {
        cerr << "Error: Expected int type in the loop initialization" << endl;
        return 0;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        cerr << "Error: Expected identifier for loop variable" << endl;
        return 0;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ASSIGN)) {
        cerr << "Error: Expected '=' in the loop initialization" << endl;
        return 0;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::INT)) {
        cerr << "Error: Expected integer literal for loop initial value" << endl;
        return 0;
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::SEMICOLON)) {
        cerr << "Error: Expected ';' after loop condition" << endl;
        return 0;
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
        return 0;
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
        return 0;
    }

    advance();

    parseBlock("FOR");

    return currentTokenIndex;
}

size_t LoopsParser::parseWhileStatement()
{
    if (!checkCurrentTokenType(TOKENS::WHILE)) {
        return 0;
    }

    cout << "Parsing WHILE Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after WHILE statement" << endl;
        return 0;
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

    advance();

    parseBlock("WHILE");

    return currentTokenIndex;
}