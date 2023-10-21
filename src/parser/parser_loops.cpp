#include "../../include/parser/parser_loops.hpp"

LoopsParser::LoopsParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void LoopsParser::parseForStatement()
{
    if (!checkCurrentTokenType(TOKENS::FOR)) {
        Error::throwError(ErrorCode::EXPECTED_KEY, "for");
    }

    cout << "Parsing FOR Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_PARENT);
    }

    advance();

    cout << "  Parsing Declaration:" << endl;

    if (!checkCurrentTokenType(TOKENS::INT_TYPE)) {
        Error::throwError(ErrorCode::INVALID_TYPE);
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        Error::throwError(ErrorCode::EXPECTED_ID);
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ASSIGN)) {
        Error::throwError(ErrorCode::EXPECTED_ASSIGN);
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::INT)) {
        Error::throwError(ErrorCode::INVALID_VALUE);
    }

    cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
         << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::SEMICOLON)) {
        Error::throwError(ErrorCode::MISSING_SEMICOLUMN);
    }

    advance();

    cout << "  Parsing Condition:" << endl;

    while (!checkCurrentTokenType(TOKENS::SEMICOLON) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::SEMICOLON)) {
        Error::throwError(ErrorCode::INVALID_VALUE);
    }

    advance();

    cout << "  Parsing Increment:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_PARENT);
    }

    parseBlock("FOR");
}

void LoopsParser::parseWhileStatement()
{
    if (!checkCurrentTokenType(TOKENS::WHILE)) {
        return;
    }

    cout << "Parsing WHILE Loop:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_PARENT);
    }

    advance();

    cout << "  Parsing Condition:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;
        advance();
    }

    parseBlock("WHILE");
}