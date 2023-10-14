#include "../../include/parser/parser_variables.hpp"

VariablesParser::VariablesParser(const vector<Token> &tokens, size_t &currentTokenIndex) : Parser(tokens, currentTokenIndex) {}

size_t VariablesParser::parseVariableStatement()
{
    if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
            checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
            checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
            checkCurrentTokenType(TOKENS::STRING_TYPE) ||
            checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
        return 0;
    }

    cout << "Parsing VARIABLE " << tokens[currentTokenIndex].getTokenTypeName() << ":" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        return 0;
    }

    cout << "  Variable Name: " << tokens[currentTokenIndex].value << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ASSIGN)) {
        return 0;
    }

    advance();

    if (!(checkCurrentTokenType(TOKENS::INT) ||
          checkCurrentTokenType(TOKENS::FLOAT) ||
          checkCurrentTokenType(TOKENS::CHAR) ||
          checkCurrentTokenType(TOKENS::STRING) ||
          checkCurrentTokenType(TOKENS::BOOLEAN))) {
        return 0;
    }

    cout << "  Variable Value: " << tokens[currentTokenIndex].value << endl;

    advance();

    return currentTokenIndex;
}