#include "../include/lexer.h"

lexer::lexer(const string &s) : input(s), position(0) {};

vector<Token> lexer::tokenize()
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
        // IF
        else if (current_char == 'i'
                    && position + 2 < input.size()
                    && input[position + 1] == 'f'
                    && !isalnum(input[position + 2])
                ) {
            tokens.push_back(Token{ TOKENS::IF, "if" });
            position += 2;
        }
        // ELSEIF
        else if (current_char == 'e'
                    && position + 6 < input.size()
                    && input[position + 1] == 'l'
                    && input[position + 2] == 's'
                    && input[position + 3] == 'e'
                    && input[position + 4] == 'i'
                    && input[position + 5] == 'f'
                    && !isalnum(input[position + 6])
                ) {
            tokens.push_back(Token{ TOKENS::ELSEIF, "elseif" });
            position += 6;
        }
        // ELSE
        else if (current_char == 'e'
                    && position + 4 < input.size()
                    && input[position + 1] == 'l'
                    && input[position + 2] == 's'
                    && input[position + 3] == 'e'
                    && !isalnum(input[position + 4])
                ) {
            tokens.push_back(Token{ TOKENS::ELSE, "else" });
            position += 4;
        }
        // FOR
        else if (current_char == 'f'
                    && position + 3 < input.size()
                    && input[position + 1] == 'o'
                    && input[position + 2] == 'r'
                    && !isalnum(input[position + 3])
                ) {
            tokens.push_back(Token{ TOKENS::FOR, "for" });
            position += 3;
        }
        // WHILE
        else if (current_char == 'w'
                    && position + 5 < input.size()
                    && input[position + 1] == 'h'
                    && input[position + 2] == 'i'
                    && input[position + 3] == 'l'
                    && input[position + 4] == 'e'
                    && !isalnum(input[position + 5])
                ) {
            tokens.push_back(Token{ TOKENS::WHILE, "while" });
            position += 5;
        }
        // FUNC
        else if (current_char == 'f'
                 && position + 2 < input.size()
                 && input[position + 1] == 'n'
                 && !isalnum(input[position + 2])
                ) {
            tokens.push_back(Token{ TOKENS::FUNC, "fn" });
            position += 2;
        }
        // RETURN
        else if (current_char == 'r'
                 && position + 6 < input.size()
                 && input[position + 1] == 'e'
                 && input[position + 2] == 't'
                 && input[position + 3] == 'u'
                 && input[position + 4] == 'r'
                 && input[position + 5] == 'n'
                 && !isalnum(input[position + 6])
                ) {
            tokens.push_back(Token{ TOKENS::RETURN, "return" });
            position += 6;
        }
        // CLASS
        else if (current_char == 'c'
                 && position + 5 < input.size()
                 && input[position + 1] == 'l'
                 && input[position + 2] == 'a'
                 && input[position + 3] == 's'
                 && input[position + 4] == 's'
                 && !isalnum(input[position + 5])
                ) {
            tokens.push_back(Token{ TOKENS::CLASS, "class" });
            position += 5;
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
        // INCR
        else if (current_char == '+' && position + 1 < input.size() && input[position + 1] == '+') {
            tokens.push_back(Token{ TOKENS::INCR, "++" });
            position++;
        }
        // PLUS
        else if (current_char == '+') {
            tokens.push_back(Token{ TOKENS::PLUS, "+" });
            position++;
        }
        // DECR
        else if (current_char == '-' && position + 1 < input.size() && input[position + 1] == '-') {
            tokens.push_back(Token{ TOKENS::DECR, "--" });
            position++;
        }
        // MINUS
        else if (current_char == '-') {
            tokens.push_back(Token{ TOKENS::MINUS, "-" });
            position++;
        }
        // MUL
        else if (current_char == '*') {
            tokens.push_back(Token{ TOKENS::MUL, "*" });
            position++;
        }
        // DIV
        else if (current_char == '/') {
            tokens.push_back(Token{ TOKENS::DIV, "/" });
            position++;
        }
        // RPAREN
        else if (current_char == '(') {
            tokens.push_back(Token{ TOKENS::LPAREN, "(" });
            position++;
        }
        // LPAREN
        else if (current_char == ')') {
            tokens.push_back(Token{ TOKENS::RPAREN, ")" });
            position++;
        }
        // EQUAL
        else if (current_char == '=' && position + 1 < input.size() && input[position + 1] == '=') {
            tokens.push_back(Token{ TOKENS::EQUAL, "==" });
            position++;
        }
        // NOT EQUAL
        else if (current_char == '!' && position + 1 < input.size() && input[position + 1] == '=') {
            tokens.push_back(Token{ TOKENS::NOT_EQUAL, "!=" });
            position++;
        }
        // ASSIGN
        else if (current_char == '=') {
            tokens.push_back(Token{ TOKENS::ASSIGN, "=" });
            position++;
        }
        // LESS THAN OR EQUAL
        else if (current_char == '<' && position + 1 < input.size() && input[position + 1] == '=') {
            tokens.push_back(Token{ TOKENS::LESS_THAN_OR_EQUAL, "<=" });
            position++;
        }
        // LESS THAN
        else if (current_char == '<') {
            tokens.push_back(Token{ TOKENS::LESS_THAN, "<" });
            position++;
        }
        // GREATER THAN OR EQUAL
        else if (current_char == '>' && position + 1 < input.size() && input[position + 1] == '=') {
            tokens.push_back(Token{ TOKENS::GREATER_THAN_OR_EQUAL, ">=" });
            position++;
        }
        // GREATER THAN
        else if (current_char == '>') {
            tokens.push_back(Token{ TOKENS::GREATER_THAN, ">" });
            position++;
        }
        // AND
        else if (current_char == '&' && position + 1 < input.size() && input[position + 1] == '&') {
            tokens.push_back(Token{ TOKENS::AND, "&&" });
            position++;
        }
        // OR
        else if (current_char == '|' && position + 1 < input.size() && input[position + 1] == '|') {
            tokens.push_back(Token{ TOKENS::OR, "||" });
            position++;
        }
        // NOT
        else if (current_char == '!') {
            tokens.push_back(Token{ TOKENS::NOT, "!" });
            position++;
        }
        // WHITESPACE
        else if (current_char == ' ') {
            position++;
        }
        // INVALID
        else {
            tokens.push_back(Token{ TOKENS::INVALID, std::string(1, current_char) });
            position++;
        }
    }
    return tokens;
}

Token lexer::processNumber(vector<Token> tokens)
{
    string result;
    bool hasDecimal = false;

    while (position < input.size() && (isdigit(input[position]) || input[position] == '.')) {
        if (input[position] == '.') {
            if (hasDecimal) {
                tokens.push_back(Token{ TOKENS::INVALID, result });
                return Token{ TOKENS::INVALID, "" };
            }
            hasDecimal = true;
        }

        result += input[position];
        position++;
    }

    if (result.back() == '.') {
        tokens.push_back(Token{ TOKENS::INVALID, result });
        return Token{ TOKENS::INVALID, "" };
    }

    return hasDecimal ? Token{ TOKENS::FLOAT, result } : Token{ TOKENS::INT, result };
}

Token lexer::processId()
{
    string result;

    while (position < input.size() && (isalnum(input[position]) || input[position] == '_')) {
        result += input[position];
        position++;
    }

    return Token { TOKENS::ID, result };
}

Token lexer::processChar()
{
    position++;

    char charValue = input[position];

    position++;
    if (input[position] == '\'') {
        position++;
        return Token{ TOKENS::CHAR, std::string(1, charValue) };
    }

    return Token{ TOKENS::INVALID, "" };
}

Token lexer::processString()
{
    position++;
    string stringValue;

    while (position < input.size() && input[position] != '\"') {
        stringValue += input[position];
        position++;
    }

    if (position < input.size() && input[position] == '\"') {
        position++;
        return Token{ TOKENS::STRING, stringValue };
    }

    return Token{ TOKENS::INVALID, "" };
}