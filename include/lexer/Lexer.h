#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>

using namespace std;

enum class TOKENS {
    INT,
    FLOAT,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END,
    INVALID
};

struct Token {
    TOKENS type;
    string value;
};

class Lexer {
public:
    Lexer(const string& s);

    vector<Token> tokenize();

private:
    Token processNumber();

private:
    string input;
    size_t position;
};

#endif