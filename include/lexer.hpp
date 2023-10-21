#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

enum class TOKENS
{
    // VALUES
    INT,
    FLOAT,
    CHAR,
    STRING,
    BOOLEAN,
    // KEYS
    IF,
    ELSEIF,
    ELSE,
    FOR,
    WHILE,
    FUNC,
    RETURN,
    CLASS,
    THIS,
    // KEYS TYPE
    INT_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    STRING_TYPE,
    BOOLEAN_TYPE,
    // DEF
    ID,
    // OPERATORS CALCUL
    INCR,
    DECR,
    PLUS_EQUAL,
    MINUS_EQUAL,
    MUL_EQUAL,
    DIV_EQUAL,
    PLUS,
    MINUS,
    MUL,
    DIV,
    // PARENTS
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACK,
    CLOSE_BRACK,
    // ASSIGNATION VARIABLE
    ASSIGN,
    // OPERATORS
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN_OR_EQUAL,
    AND,
    OR,
    NOT,
    // UTILS
    DOT,
    COMMA,
    SEMICOLON,
    END,
    INVALID,

    SENTINEL
};

struct Token
{
    TOKENS type;
    string value;

    const char* tokenTypeNames[static_cast<int>(TOKENS::SENTINEL)] = {
            "INT", "FLOAT", "CHAR", "STRING", "BOOLEAN",
            "IF", "ELSEIF", "ELSE", "FOR", "WHILE", "FUNC", "RETURN", "CLASS", "THIS",
            "INT_TYPE", "FLOAT_TYPE", "CHAR_TYPE", "STRING_TYPE", "BOOLEAN_TYPE",
            "ID",
            "INCR", "DECR", "PLUS_EQUAL", "MINUS_EQUAL", "MUL_EQUAL", "DIV_EQUAL",
            "PLUS", "MINUS", "MUL", "DIV",
            "OPEN_PAREN", "CLOSE_PAREN", "OPEN_BRACK", "CLOSE_BRACK",
            "ASSIGN",
            "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_THAN_OR_EQUAL", "GREATER_THAN_OR_EQUAL",
            "AND", "OR", "NOT",
            "DOT", "COMMA", "SEMICOLON",
            "END",
            "INVALID"
    };

    const char * getTokenTypeName() const {
        return tokenTypeNames[static_cast<int>(type)];
    }
};

class Lexer
{
public:
    explicit Lexer(string s);

    vector<Token> tokenize();

private:
    string input;
    size_t position;

    Token processNumber();
    Token processId();
    Token processChar();
    Token processString();

    const unordered_map<string, TOKENS> KEYWORDS = {
            {"if", TOKENS::IF},
            {"elseif", TOKENS::ELSEIF},
            {"else", TOKENS::ELSE},
            {"for", TOKENS::FOR},
            {"while", TOKENS::WHILE},
            {"fn", TOKENS::FUNC},
            {"rn", TOKENS::RETURN},
            {"class", TOKENS::CLASS},
            {"int", TOKENS::INT_TYPE},
            {"float", TOKENS::FLOAT_TYPE},
            {"char", TOKENS::CHAR_TYPE},
            {"string", TOKENS::STRING_TYPE},
            {"boolean", TOKENS::BOOLEAN_TYPE},
            {"true", TOKENS::BOOLEAN},
            {"false", TOKENS::BOOLEAN},
            {"this", TOKENS::THIS}
    };

    const unordered_map<string, TOKENS> OPERATORS = {
            {"++", TOKENS::INCR},
            {"--", TOKENS::DECR},
            {"+=", TOKENS::PLUS_EQUAL},
            {"-=", TOKENS::MINUS_EQUAL},
            {"*=", TOKENS::MUL_EQUAL},
            {"/=", TOKENS::DIV_EQUAL},
            {"+", TOKENS::PLUS},
            {"-", TOKENS::MINUS},
            {"*", TOKENS::MUL},
            {"/", TOKENS::DIV},
            {"==", TOKENS::EQUAL},
            {"!=", TOKENS::NOT_EQUAL},
            {"=", TOKENS::ASSIGN},
            {"<=", TOKENS::LESS_THAN_OR_EQUAL},
            {"<", TOKENS::LESS_THAN},
            {">=", TOKENS::GREATER_THAN_OR_EQUAL},
            {">", TOKENS::GREATER_THAN},
            {"&&", TOKENS::AND},
            {"||", TOKENS::OR},
            {"!", TOKENS::NOT},
            {"(", TOKENS::OPEN_PAREN},
            {")", TOKENS::CLOSE_PAREN},
            {"{", TOKENS::OPEN_BRACK},
            {"}", TOKENS::CLOSE_BRACK},
            {",", TOKENS::COMMA},
            {";", TOKENS::SEMICOLON},
            {".", TOKENS::DOT},
    };

    bool isKeyword(const string &str);
    static bool isLineBreak(char c);
};

#include "errors.hpp"

#endif