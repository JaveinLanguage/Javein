#include "../include/lexer.hpp"

Lexer::Lexer(const string &s) : input(s), position(0) {};

vector<Token> Lexer::tokenize()
{
    vector<Token> tokens;
    while (true) {
            // END
        if (position >= input.size()) {
            tokens.push_back(Token{ TOKENS::END, "" });
            break;
        }

        const char current_char = input[position];

            // INT
        if (isdigit(current_char)) {
            tokens.push_back(processNumber(tokens));
        }
            // IDENTIFIER
        else if (isalpha(current_char) || current_char == '_') {
            tokens.push_back(processId());
        }
            // CHAR
        else if (current_char == '\'') {
            tokens.push_back(processChar());
        }
            // STRING
        else if (current_char == '\"') {
            tokens.push_back(processString());
        }
            // OPERATORS
        else if (OPERATORS.count(string(1, current_char)) > 0) {
            string op(1, current_char);

            while (position + 1 < input.size() && OPERATORS.count(op + input[position + 1]) > 0) {
                op += input[position + 1];
                position++;
            }

            tokens.push_back(Token{ OPERATORS.at(op), op });
            position++;
        }
            // Ignore whitespace
        else if (isspace(current_char)) {
            position++;
        }
            // Invalid character
        else {
            tokens.push_back(Token{ TOKENS::INVALID, string(1, current_char) });
            position++;
        }
    }

    if (position >= input.size()) {
        tokens.push_back(Token{ TOKENS::INVALID, "Unexpected end of input" });
    }

    return tokens;
}

Token Lexer::processNumber(vector<Token> tokens)
{
    string result;
    bool hasDecimal = false;

    while (position < input.size() && (isdigit(input[position]) || input[position] == '.')) {
        if (input[position] == '.') {
            if (hasDecimal) {
                tokens.push_back(Token{ TOKENS::INVALID, result });
                return Token{ TOKENS::INVALID, "Invalid number" };
            }
            hasDecimal = true;
        }

        result += input[position];
        position++;
    }

    if (result.empty() || result.back() == '.') {
        tokens.push_back(Token{ TOKENS::INVALID, result });
        return Token{ TOKENS::INVALID, "Invalid number" };
    }

    return hasDecimal ? Token{ TOKENS::FLOAT, result } : Token{ TOKENS::INT, result };
}

Token Lexer::processId() {
    string result;

    while (position < input.size() && (isalnum(input[position]) || input[position] == '_')) {
        result += input[position];
        position++;
    }

    if (isKeyword(result)) {
        auto keywordIt = KEYWORDS.find(result);
        if (keywordIt != KEYWORDS.end()) {
            return Token{ keywordIt->second, result };
        }
    }

    if (position < input.size() && input[position] == '=') {
        result += input[position];
        position++;

        while (position < input.size() && (isalnum(input[position]) || input[position] == '_')) {
            result += input[position];
            position++;
        }

        return Token{TOKENS::ID, result};
    }

    return Token{TOKENS::ID, result};
}
Token Lexer::processChar()
{
    position++;

    if (position >= input.size()) {
        return Token{ TOKENS::INVALID, "Unexpected end of input" };
    }

    char charValue = input[position];

    position++;
    if (position >= input.size() || input[position] != '\'') {
        return Token{ TOKENS::INVALID, "Invalid character literal" };
    }

    position++;
    return Token{ TOKENS::CHAR, string(1, charValue) };
}

Token Lexer::processString()
{
    position++;
    string stringValue;

    while (position < input.size() && input[position] != '\"') {
        stringValue += input[position];
        position++;
    }

    if (position >= input.size() || input[position] != '\"') {
        return Token{ TOKENS::INVALID, "Unterminated string literal" };
    }

    position++;
    return Token{ TOKENS::STRING, stringValue };
}

bool Lexer::isKeyword(const string &str) {
    return KEYWORDS.count(str) > 0;
}