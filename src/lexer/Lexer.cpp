#include "../../include/lexer/Lexer.h"
#include <iostream>
#include <vector>

using namespace std;

Lexer::Lexer(const string& s) : input(s), position(0) {};

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (true) {
        if (position >= input.size()) {
            tokens.push_back(Token{ TOKENS::END, "" });
            break;
        }

        const char current_char = input[position];
        if (isdigit(current_char)) {
            tokens.push_back(processNumber());
        }
        else if (current_char == '+') {
            tokens.push_back(Token{ TOKENS::PLUS, "+" });
            position++;
        }
        else if (current_char == '-') {
            tokens.push_back(Token{ TOKENS::MINUS, "-" });
            position++;
        }
        else if (current_char == '*') {
            tokens.push_back(Token{ TOKENS::MUL, "*" });
            position++;
        }
        else if (current_char == '/') {
            tokens.push_back(Token{ TOKENS::DIV, "/" });
            position++;
        }
        else if (current_char == '(') {
            tokens.push_back(Token{ TOKENS::LPAREN, "(" });
            position++;
        }
        else if (current_char == ')') {
            tokens.push_back(Token{ TOKENS::RPAREN, ")" });
            position++;
        }
        else {
            // Invalid token
            tokens.push_back(Token{ TOKENS::INVALID, std::string(1, current_char) });
            position++;
        }
    }
    return tokens;
}

Token Lexer::processNumber() {
    string result;
    while (position < input.size() && isdigit(input[position])) {
        result += input[position];
        position++;
    }
    return Token{ TOKENS::INT, result };
}