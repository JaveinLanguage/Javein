#include "../../include/parser/parser_constructors.hpp"

ConstructorParser::ConstructorParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void ConstructorParser::parseConstructor(const string &className)
{
    if (!hasConstructor(className)) {
        return;
    }

    cout << "    Parsing constructor : " + tokens[currentTokenIndex].value << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_PARENT);
    }

    advance();

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
              checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
              checkCurrentTokenType(TOKENS::STRING_TYPE) ||
              checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
              checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
            Error::throwError(ErrorCode::INVALID_PARAM_TYPE);
            return;
        }

        string paramType = tokens[currentTokenIndex].value;
        cout << "      Parameter Type: " << paramType << endl;

        advance();

        if (!checkCurrentTokenType(TOKENS::ID)) {
            Error::throwError(ErrorCode::EXPECTED_ID);
        }

        string paramName = tokens[currentTokenIndex].value;
        cout << "      Parameter Name: " << paramName << endl;

        advance();

        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();

            if (checkCurrentTokenType(TOKENS::INT) ||
                checkCurrentTokenType(TOKENS::FLOAT) ||
                checkCurrentTokenType(TOKENS::STRING) ||
                checkCurrentTokenType(TOKENS::CHAR) ||
                checkCurrentTokenType(TOKENS::BOOLEAN)) {
                string defaultValue = tokens[currentTokenIndex].value;
                cout << "        Default Value: " << defaultValue << endl;
                advance();
            } else {
                Error::throwError(ErrorCode::INVALID_VALUE);
            }
        }

        if (checkCurrentTokenType(TOKENS::COMMA)) {
            advance();
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_PARENT);
    }

    parseBlock("CONSTRUCTOR");
}

bool ConstructorParser::hasConstructor(const string &className) {
    return className == tokens[currentTokenIndex].value;
}