#include "../include/parser.hpp"

parser::parser(const vector<Token> &tokens, const size_t currentTokenIndex) : tokens(tokens), currentTokenIndex(currentTokenIndex) {}

void parser::parse()
{
    while (currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::IF)) {
            ConditionsParser conditionsParser(tokens, currentTokenIndex);
            currentTokenIndex = conditionsParser.parseIfStatement();
        }
        else if (checkCurrentTokenType(TOKENS::FOR)) {
            LoopsParser loopsParser(tokens, currentTokenIndex);
            currentTokenIndex = loopsParser.parseForStatement();
        }
        else if (checkCurrentTokenType(TOKENS::WHILE)) {
            LoopsParser loopsParser(tokens, currentTokenIndex);
            currentTokenIndex = loopsParser.parseWhileStatement();
        }
        else if (checkCurrentTokenType(TOKENS::FUNC)) {
            FunctionsParser functionsParser(tokens, currentTokenIndex);
            currentTokenIndex = functionsParser.parseFunction();
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

// UTILS

void parser::parseBlock(const string& blockType)
{
    advance();

    cout << "  Parsing Block:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_BRACK) && currentTokenIndex < tokens.size()) {
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();

        if (currentTokenIndex >= tokens.size()) {
            cerr << "Error: Unexpected end of tokens inside " << blockType << " statement" << endl;
            return;
        }
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
    if (currentTokenIndex < tokens.size() - 1) {
        if (tokens[currentTokenIndex + 1].type == TOKENS::END) {
            cout << "Parsing complete. Reached END token." << endl;
            exit(1);
        }

        currentTokenIndex++;
    } else {
        cerr << "Error: Attempted to advance beyond the end of tokens." << endl;
        exit(1);
    }
}