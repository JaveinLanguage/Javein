#include "../include/parser.h"

Parser::Parser(const vector<Token>& tokens) : tokens(tokens), currentPos(0) {}

void Parser::parse() {
    while (currentPos < tokens.size()) {
        parseStatement();
    }
}

void Parser::parseStatement() {
    if (match(TOKENS::IF)) {
        parseIfStatement();
    }
}

void Parser::parseIfStatement() {
    if (!match(TOKENS::LPAREN)) {
        cout << "Error: Expected opening parenthesis.\n";
        return;
    }

    while (currentPos < tokens.size() && tokens[currentPos].type != TOKENS::RPAREN) {
        currentPos++;
    }

    if (!match(TOKENS::RPAREN)) {
        cout << "Error: Expected closing parenthesis.\n";
        return;
    }

    parseStatement();

    while (match(TOKENS::ELSEIF)) {
        parseIfStatement();
    }

    if (match(TOKENS::ELSE)) {
        parseStatement();
    }

    cout << "Success! Parsed an if statement.\n";
}


bool Parser::match(TOKENS expectedType) {
    if (currentPos < tokens.size() && tokens[currentPos].type == expectedType) {
        currentPos++;
        return true;
    }
    return false;
}
