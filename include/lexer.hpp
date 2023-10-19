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
    // COMMENT
    LINE_COMMENT,
    BLOCK_COMMENT,
    // UTILS
    COMMA,
    SEMICOLON,
    END,
    INVALID
};

struct Token
{
    TOKENS type;
    string value;

     string getTokenTypeName() const {
        switch (type) {
            case TOKENS::INT: return "INT";
            case TOKENS::FLOAT: return "FLOAT";
            case TOKENS::CHAR: return "CHAR";
            case TOKENS::STRING: return "STRING";
            case TOKENS::BOOLEAN: return "BOOLEAN";
            case TOKENS::ID: return "ID";
            case TOKENS::IF: return "IF";
            case TOKENS::ELSEIF: return "ELSEIF";
            case TOKENS::ELSE: return "ELSE";
            case TOKENS::FOR: return "FOR";
            case TOKENS::WHILE: return "WHILE";
            case TOKENS::FUNC: return "FUNC";
            case TOKENS::RETURN: return "RETURN";
            case TOKENS::INT_TYPE: return "INT_TYPE";
            case TOKENS::FLOAT_TYPE: return "FLOAT_TYPE";
            case TOKENS::CHAR_TYPE: return "CHAR_TYPE";
            case TOKENS::STRING_TYPE: return "STRING_TYPE";
            case TOKENS::BOOLEAN_TYPE: return "BOOLEAN_TYPE";
            case TOKENS::CLASS: return "CLASS";
            case TOKENS::INCR: return "INCREMENTATION";
            case TOKENS::DECR: return "DECREMENTATION";
            case TOKENS::PLUS_EQUAL: return "PLUS_EQUAL";
            case TOKENS::MINUS_EQUAL: return "MINUS_EQUAL";
            case TOKENS::MUL_EQUAL: return "MUL_EQUAL";
            case TOKENS::DIV_EQUAL: return "DIV_EQUAL";
            case TOKENS::PLUS: return "PLUS";
            case TOKENS::MINUS: return "MINUS";
            case TOKENS::MUL: return "MULTIPLY";
            case TOKENS::DIV: return "DIVIDE";
            case TOKENS::OPEN_PAREN: return "OPEN_PAREN";
            case TOKENS::CLOSE_PAREN: return "CLOSE_PAREN";
            case TOKENS::OPEN_BRACK: return "OPEN_BRACK";
            case TOKENS::CLOSE_BRACK: return "CLOSE_BRACK";
            case TOKENS::END: return "END";
            case TOKENS::ASSIGN: return "ASSIGN";
            case TOKENS::EQUAL: return "EQUAL";
            case TOKENS::NOT_EQUAL: return "NOT_EQUAL";
            case TOKENS::LESS_THAN: return "LESS_THAN";
            case TOKENS::GREATER_THAN: return "GREATER_THAN";
            case TOKENS::LESS_THAN_OR_EQUAL: return "LESS_THAN_OR_EQUAL";
            case TOKENS::GREATER_THAN_OR_EQUAL: return "GREATER_THAN_OR_EQUAL";
            case TOKENS::AND: return "AND";
            case TOKENS::OR: return "OR";
            case TOKENS::NOT: return "NOT";
            case TOKENS::LINE_COMMENT: return "LINE_COMMENT";
            case TOKENS::BLOCK_COMMENT: return "BLOCK_COMMENT";
            case TOKENS::COMMA: return "COMMA";
            case TOKENS::SEMICOLON: return "SEMICOLON";
            case TOKENS::INVALID: return "INVALID";
        }
        return "";
    }
};

class Lexer
{
public:
    explicit Lexer(const string& s);

    vector<Token> tokenize();

private:
    string input;
    size_t position;

    Token processNumber(vector<Token> tokens);
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
            {"false", TOKENS::BOOLEAN}
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
            {";", TOKENS::SEMICOLON}
    };

    bool isKeyword(const string &str);
};

#endif