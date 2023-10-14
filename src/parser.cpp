#include "../include/parser.h"

parser::parser(const vector<Token> &tokens) : tokens(tokens), currentTokenIndex(0) {}

void parser::parse()
{
    while (currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::IF)) {
            parseIfStatement();
        }
        else if (checkCurrentTokenType(TOKENS::FOR)) {
            parseForStatement();
        }
        else if (checkCurrentTokenType(TOKENS::WHILE)) {
            parseWhileStatement();
        }
        else {
            if (currentTokenIndex >= tokens.size()) {
                break;
            }

            cerr << "Error: Unexpected token at position "
                 << currentTokenIndex << ": "
                 << tokens[currentTokenIndex].value << endl;
            advance();
        }
    }
}

void parser::parseIfStatement()
{
    if (!checkCurrentTokenType(TOKENS::IF)) {
        return;
    }

    parseConditional("IF");

    while (checkCurrentTokenType(TOKENS::ELSEIF)) {
        parseConditional("ELSE IF");
    }

    if (checkCurrentTokenType(TOKENS::ELSE)) {
        cout << "Parsing ELSE Statement:" << endl;
        advance();
        parseBlock("ELSE");
    }
}

void parser::parseConditional(const string& statementType)
{
    cout << "Parsing " << statementType << " Statement:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after " << statementType << " statement" << endl;
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
        cerr << "Error: Expected ')' after " << statementType << " statement" << endl;
        return;
    }

    advance();

    parseBlock(statementType);
}

void parser::parseForStatement()
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

    advance();

    parseBlock("FOR");
}

void parser::parseWhileStatement()
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

    advance();

    parseBlock("WHILE");
}

// UTILS

void parser::parseBlock(const string& blockType)
{
    advance();

    cout << "  Parsing Block:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_BRACK) && currentTokenIndex < tokens.size()) {
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_BRACK)) {
        cerr << "Error: Expected '}' after " << blockType << " statement" << endl;
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