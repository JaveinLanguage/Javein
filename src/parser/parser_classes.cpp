#include "../../include/parser/parser_classes.hpp"

ClassesParser::ClassesParser(const vector<Token> &tokens, size_t &currentTokenIndex) : Parser(tokens, currentTokenIndex) {}

size_t ClassesParser::parseClassStatement()
{
    if (!checkCurrentTokenType(TOKENS::CLASS)) {
        return 0;
    }

    cout << "Parsing Class" << endl;

    advance();

    string className = tokens[currentTokenIndex].value;
    cout << "  Class Name: " << className << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after class name" << endl;
        return 0;
    }

    advance();

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (!(checkCurrentTokenType(TOKENS::INT_TYPE) ||
              checkCurrentTokenType(TOKENS::FLOAT_TYPE) ||
              checkCurrentTokenType(TOKENS::STRING_TYPE) ||
              checkCurrentTokenType(TOKENS::CHAR_TYPE) ||
              checkCurrentTokenType(TOKENS::BOOLEAN_TYPE))) {
            cerr << "Error: Expected parameter type" << endl;
            return 0;
        }

        string paramType = tokens[currentTokenIndex].value;
        cout << "    Parameter Type: " << paramType << endl;

        advance();

        if (!checkCurrentTokenType(TOKENS::ID)) {
            cerr << "Error: Expected parameter name" << endl;
            return 0;
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
                return 0;
            }
        }

        if (checkCurrentTokenType(TOKENS::COMMA)) {
            advance();
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        cerr << "Error: Expected ')' after class parameters" << endl;
        return 0;
    }

    advance();

    cout << "  Parsing Block:" << endl;

    if (!checkCurrentTokenType(TOKENS::OPEN_BRACK)) {
        cerr << "Error: Expected '{' after statement" << endl;
        return 0;
    }

    advance();

    while (tokens[currentTokenIndex].value != className || checkCurrentTokenType(TOKENS::FUNC) && currentTokenIndex < tokens.size()) {
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
                cout << "      Default Value: " << defaultValue << endl;
                advance();
            } else {
                cerr << "Error: Expected default parameter value" << endl;
                return 0;
            }
        }
    }

    ConstructorParser constructorParser(tokens, currentTokenIndex);
    constructorParser.parseConstructor(className);

    cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

    return currentTokenIndex;
}