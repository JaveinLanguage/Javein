#include "../include/parser.hpp"

Parser::Parser(const vector<Token> &tokens, int &currentIndex) : tokens(tokens), currentTokenIndex(currentIndex) {}

void Parser::parse()
{
    while (currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::INT_TYPE) ||
              checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
              checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
              checkCurrentTokenType(TOKENS::STRING_TYPE) ||
              checkCurrentTokenType(TOKENS::BOOLEAN_TYPE)) {
            VariablesParser variablesParser(tokens, currentTokenIndex);
            variablesParser.parseVariableStatement();
        }
        else if (checkCurrentTokenType(TOKENS::IF)) {
            ConditionsParser conditionsParser(tokens, currentTokenIndex);
            conditionsParser.parseIfStatement();
        }
        else if (checkCurrentTokenType(TOKENS::FOR)) {
            LoopsParser loopsParser(tokens, currentTokenIndex);
            loopsParser.parseForStatement();
        }
        else if (checkCurrentTokenType(TOKENS::WHILE)) {
            LoopsParser loopsParser(tokens, currentTokenIndex);
            loopsParser.parseWhileStatement();
        }
        else if (checkCurrentTokenType(TOKENS::FUNC)) {
            FunctionsParser functionsParser(tokens, currentTokenIndex);
            functionsParser.parseFunction();
        }
        else if (checkCurrentTokenType(TOKENS::CLASS)) {
            ClassesParser classesParser(tokens, currentTokenIndex);
            classesParser.parseClassStatement();
        }
        else {
            if (currentTokenIndex >= tokens.size()) {
                Error::throwError(ErrorCode::UNEXPECTED_END);
            }
            else {
                Error::throwError(ErrorCode::INVALID_TOKEN);
            }
        }
    }
}

// UTILS

void Parser::parseBlock(const string &blockType)
{
    advance();

    cout << "  Parsing Block:" << endl;

    if (!checkCurrentTokenType(TOKENS::OPEN_BRACK)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_BRACK);
    }

    advance();

    bool hasReturnStatement = false;

    while (!checkCurrentTokenType(TOKENS::CLOSE_BRACK) && currentTokenIndex < tokens.size()) {
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

        if (blockType == "FUNCTION" && checkCurrentTokenType(TOKENS::RETURN)) {
            hasReturnStatement = true;
        }

        advance();

        if (currentTokenIndex >= tokens.size()) {
            Error::throwError(ErrorCode::UNEXPECTED_END_IN_BLOCK, blockType);
            return;
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_BRACK)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_BRACK);
    }

    advance();

    if (blockType == "FUNCTION" && !hasReturnStatement) {
        Error::throwError(ErrorCode::EXPECTED_RETURN_VALUE);
    }
}

bool Parser::checkCurrentTokenType(TOKENS expectedType)
{
    return tokens[currentTokenIndex].type == expectedType;
}

void Parser::advance()
{
    if (currentTokenIndex < tokens.size() - 1) {
        if (tokens[currentTokenIndex + 1].type == TOKENS::END) {
            cout << "Parsing complete. Reached END token." << endl;
            exit(0);
        }

        currentTokenIndex++;
    } else {
        Error::throwError(ErrorCode::ATTEMPT_TO_ADVANCE_BEYOND_END);
    }
}