#include "../../include/parser/parser_functions.hpp"

FunctionsParser::FunctionsParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void FunctionsParser::parseFunction()
{
    if (!checkCurrentTokenType(TOKENS::FUNC)) {
        return;
    }

    advance();

    if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
          checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
          checkCurrentTokenType(TOKENS::STRING_TYPE) ||
          checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
          checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
        cerr << "Error: Expected return type after 'fn'" << endl;
        return;
    }

    string returnType = tokens[currentTokenIndex].value;
    cout << "Parsing Function with return type: " << returnType << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        cerr << "Error: Expected function name after return type" << endl;
        return;
    }

    string functionName = tokens[currentTokenIndex].value;
    cout << "  Function Name: " << functionName << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after function name" << endl;
        return;
    }

    advance();

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
              checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
              checkCurrentTokenType(TOKENS::STRING_TYPE) ||
              checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
              checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
            cerr << "Error: Expected parameter type" << endl;
            return;
        }

        string paramType = tokens[currentTokenIndex].value;
        cout << "    Parameter Type: " << paramType << endl;

        advance();

        if (!checkCurrentTokenType(TOKENS::ID)) {
            cerr << "Error: Expected parameter name" << endl;
            return;
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
                cerr << "Error: Expected default parameter value" << endl;
                return;
            }
        }

        if (checkCurrentTokenType(TOKENS::COMMA)) {
            advance();
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        cerr << "Error: Expected ')' after function parameters" << endl;
        return;
    }

    parseBlock("FUNCTION");
}