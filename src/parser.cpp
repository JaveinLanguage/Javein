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
    else if (match(TOKENS::FOR)) {
        parseForStatement();
    }
    else if (match(TOKENS::WHILE)) {
        parseWhileStatement();
    }
    else if (match(TOKENS::FUNC)) {
        parseFunctionDeclaration();
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

void Parser::parseWhileStatement() {
    if (!match(TOKENS::LPAREN)) {
        cout << "Error: Expected opening parenthesis.\n";
        return;
    }

    if (!match(TOKENS::RPAREN)) {
        cout << "Error: Expected closing parenthesis.\n";
        return;
    }

    parseStatement();

    cout << "Success! Parsed a while statement.\n";
}

void Parser::parseForStatement() {
    if (!match(TOKENS::LPAREN)) {
        cout << "Error: Expected opening parenthesis.\n";
        return;
    }


    if (!match(TOKENS::RPAREN)) {
        cout << "Error: Expected closing parenthesis.\n";
        return;
    }

    parseStatement();

    cout << "Success! Parsed a for statement.\n";
}

void Parser::parseFunctionDeclaration() {

    cout << "Success! Parsed a function declaration.\n";
}

void Parser::parseReturnStatement() {

    cout << "Success! Parsed a return statement.\n";
}

bool Parser::match(TOKENS expectedType) {
    if (currentPos < tokens.size() && tokens[currentPos].type == expectedType) {
        currentPos++;
        return true;
    }
    return false;
}
