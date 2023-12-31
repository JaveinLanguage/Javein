#include "../include/lexer.hpp"

Lexer::Lexer(string s) : input(std::move(s)), position(0) {};

vector<Token> Lexer::tokenize()
{
    vector<Token> tokens;
    while (true) {
            // END
        if (position >= input.size()) {
            tokens.push_back(Token{TOKENS::END, ""});
            break;
        }

        const char current_char = input[position];

           // LINE COMMENT
        if (current_char == '$' && position + 1 < input.size() && input[position + 1] == '$') {
            while (position < input.size() && !isLineBreak(input[position])) {
                position++;
            }
        }
            // BLOCK COMMENT
        else if (current_char == '/' && position + 1 < input.size() && input[position + 1] == '$') {
            position += 2;

            while (position + 1 < input.size() && !(input[position] == '$' && input[position + 1] == '/')) {
                position++;
            }

            position += 2;
        }
            // INT
        else if (isdigit(current_char)) {
            tokens.push_back(processNumber());
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

            tokens.push_back(Token{OPERATORS.at(op), op});
            position++;
        }
            // IGNORE
        else if (isspace(current_char)) {
            position++;
        }
            // INVALID
        else {
            tokens.push_back(Token{TOKENS::INVALID, string(1, current_char)});
            position++;
        }
    }

    return tokens;
}

Token Lexer::processNumber()
{
    string result;
    bool hasDecimal = false;

    while (position < input.size() && (isdigit(input[position]) || input[position] == '.')) {
        if (input[position] == '.') {
            if (hasDecimal) {
                Error::throwError(ErrorCode::INVALID_NUMBER);
            }
            hasDecimal = true;
        }

        result += input[position];
        position++;
    }

    if (result.empty() || result.back() == '.') {
        Error::throwError(ErrorCode::INVALID_NUMBER);
    }

    return hasDecimal ? Token{TOKENS::FLOAT, result} : Token{TOKENS::INT, result};
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
            return Token{keywordIt->second, result};
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
        Error::throwError(ErrorCode::UNEXPECTED_END_INPUT);
    }

    char charValue = input[position];

    position++;
    if (position >= input.size() || input[position] != '\'') {
        Error::throwError(ErrorCode::UNTERMINATED_CHAR);
    }

    position++;
    return Token{TOKENS::CHAR, string(1, charValue)};
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
        Error::throwError(ErrorCode::UNTERMINATED_STRING);
    }

    position++;
    return Token{TOKENS::STRING, stringValue};
}

bool Lexer::isKeyword(const string &str) {
    return KEYWORDS.count(str) > 0;
}

bool Lexer::isLineBreak(char c) {
    return c == '\n' || c == '\r';
}