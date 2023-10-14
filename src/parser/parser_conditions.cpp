#include "../../include/parser/parser_conditions.hpp"

ConditionsParser::ConditionsParser(const vector<Token>& tokens, const size_t currentTokenIndex) : parser(tokens, currentTokenIndex) {}

size_t ConditionsParser::parseIfStatement()
{
    if (!checkCurrentTokenType(TOKENS::IF)) {
        return 0;
    }

    parseConditional("IF");

    while (checkCurrentTokenType(TOKENS::ELSEIF)) {
        parseConditional("ELSE IF");
    }

    if (checkCurrentTokenType(TOKENS::ELSE)) {
        cout << "Parsing ELSE Statement:" << endl;
        advance();
        parseBlock("ELSE");
    }

    return currentTokenIndex;
}

void ConditionsParser::parseConditional(const string& statementType)
{
    cout << "Parsing " << statementType << " Statement:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        cerr << "Error: Expected '(' after " << statementType << " statement" << endl;
        return;
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

        if (currentTokenIndex >= tokens.size()) {
            cerr << "Error: Unexpected end of tokens after condition in " << statementType << " statement" << endl;
            return;
        }

        if (checkCurrentTokenType(TOKENS::AND) || checkCurrentTokenType(TOKENS::OR)) {
            advance();

            if (currentTokenIndex >= tokens.size()) {
                cerr << "Error: Unexpected end of tokens after logical operator in " << statementType << " statement" << endl;
                return;
            }

            if (checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
                cerr << "Error: Expected condition after logical operator in " << statementType << " statement" << endl;
                return;
            }
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        cerr << "Error: Expected ')' after " << statementType << " statement" << endl;
        return;
    }

    advance();

    parseBlock(statementType);
}