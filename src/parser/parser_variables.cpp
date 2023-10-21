#include "../../include/parser/parser_variables.hpp"

VariablesParser::VariablesParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void VariablesParser::parseVariableStatement()
{
    if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
            checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
            checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
            checkCurrentTokenType(TOKENS::STRING_TYPE) ||
            checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
        Error::throwError(ErrorCode::INVALID_TYPE);
    }

    cout << "Parsing VARIABLE " << tokens[currentTokenIndex].getTokenTypeName() << ":" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        Error::throwError(ErrorCode::EXPECTED_ID);
    }

    cout << "  Variable Name: " << tokens[currentTokenIndex].value << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ASSIGN)) {
        Error::throwError(ErrorCode::EXPECTED_ASSIGN);
    }

    advance();

    if (!(checkCurrentTokenType(TOKENS::INT) ||
          checkCurrentTokenType(TOKENS::FLOAT) ||
          checkCurrentTokenType(TOKENS::CHAR) ||
          checkCurrentTokenType(TOKENS::STRING) ||
          checkCurrentTokenType(TOKENS::BOOLEAN))) {
        Error::throwError(ErrorCode::INVALID_VALUE);
    }

    cout << "  Variable Value: " << tokens[currentTokenIndex].value << endl;

    advance();
}