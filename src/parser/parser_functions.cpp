#include "../../include/parser/parser_functions.hpp"

FunctionsParser::FunctionsParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void FunctionsParser::parseFunction()
{
    if (!checkCurrentTokenType(TOKENS::FUNC)) {
        Error::throwError(ErrorCode::EXPECTED_KEY, "fn");
    }

    advance();

    if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
          checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
          checkCurrentTokenType(TOKENS::STRING_TYPE) ||
          checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
          checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
        Error::throwError(ErrorCode::EXPECTED_RETURN_TYPE);
    }

    string returnType = tokens[currentTokenIndex].value;
    cout << "Parsing Function with return type: " << returnType << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        Error::throwError(ErrorCode::EXPECTED_ID);
    }

    string functionName = tokens[currentTokenIndex].value;
    cout << "  Function Name: " << functionName << endl;

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
        cout << "    Parameter Type: " << paramType << endl;

        advance();

        if (!checkCurrentTokenType(TOKENS::ID)) {
            Error::throwError(ErrorCode::EXPECTED_ID);
        }

        string paramName = tokens[currentTokenIndex].value;
        cout << "    Parameter Name: " << paramName << endl;

        advance();

        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();

            if (checkCurrentTokenType(TOKENS::INT) ||
                checkCurrentTokenType(TOKENS::FLOAT) ||
                checkCurrentTokenType(TOKENS::STRING) ||
                checkCurrentTokenType(TOKENS::CHAR) ||
                checkCurrentTokenType(TOKENS::BOOLEAN)) {
                string defaultValue = tokens[currentTokenIndex].value;
                cout << "      Default Value: " << defaultValue << endl;
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

    parseBlock("FUNCTION");
}