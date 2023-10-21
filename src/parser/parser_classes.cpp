#include "../../include/parser/parser_classes.hpp"

ClassesParser::ClassesParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void ClassesParser::parseClassStatement()
{
    if (!checkCurrentTokenType(TOKENS::CLASS)) {
        Error::throwError(ErrorCode::EXPECTED_KEY, "class");
    }

    cout << "Parsing Class" << endl;

    advance();

    string className = tokens[currentTokenIndex].value;
    cout << "  Class Name: " << className << endl;

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
        }

        string paramType = tokens[currentTokenIndex].value;
        cout << "    Parameter Type: " << paramType << endl;

        advance();

        if (!checkCurrentTokenType(TOKENS::ID)) {
            Error::throwError(ErrorCode::EXPECTED_ID, "class");
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
                Error::throwError(ErrorCode::EXPECTED_DEFAULT_VALUE);
            }
        }

        if (checkCurrentTokenType(TOKENS::COMMA)) {
            advance();
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_PARENT);
    }

    advance();

    cout << "  Parsing Block:" << endl;

    if (!checkCurrentTokenType(TOKENS::OPEN_BRACK)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_BRACK);
    }

    advance();

    while (tokens[currentTokenIndex].value != className && currentTokenIndex < tokens.size()) {
        advance();

        cout << "    Parsing variable : " + tokens[currentTokenIndex].value << endl;

        advance();

        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();

            if (checkCurrentTokenType(TOKENS::INT) ||
                checkCurrentTokenType(TOKENS::FLOAT) ||
                checkCurrentTokenType(TOKENS::STRING) ||
                checkCurrentTokenType(TOKENS::CHAR) ||
                checkCurrentTokenType(TOKENS::BOOLEAN)) {
                string defaultValue = tokens[currentTokenIndex].value;

                advance();
            } else {
                Error::throwError(ErrorCode::EXPECTED_DEFAULT_VALUE);
            }
        }
    }

    ConstructorParser constructorParser(tokens, currentTokenIndex);
    constructorParser.parseConstructor(className);

    while (checkCurrentTokenType(TOKENS::FUNC) && currentTokenIndex < tokens.size()) {
        FunctionsParser functionsParser(tokens, currentTokenIndex);
        functionsParser.parseFunction();
    }

    advance();

    if (!checkCurrentTokenType(TOKENS::CLOSE_BRACK)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_BRACK);
    }
}