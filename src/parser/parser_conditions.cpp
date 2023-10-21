#include "../../include/parser/parser_conditions.hpp"

ConditionsParser::ConditionsParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void ConditionsParser::parseIfStatement()
{
    if (!checkCurrentTokenType(TOKENS::IF)) {
        Error::throwError(ErrorCode::EXPECTED_KEY, "if");
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
}

void ConditionsParser::parseConditional(const string& statementType)
{
    cout << "Parsing " << statementType << " Statement:" << endl;

    advance();

    if (!checkCurrentTokenType(TOKENS::OPEN_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_OPEN_PARENT);
    }

    advance();

    cout << "  Parsing Condition:" << endl;

    while (!checkCurrentTokenType(TOKENS::CLOSE_PAREN) && currentTokenIndex < tokens.size()) {
        if (checkCurrentTokenType(TOKENS::OPEN_BRACK)) {
            Error::throwError(ErrorCode::EXPECTED_CLOSE_PARENT);
        }

        if (checkCurrentTokenType(TOKENS::ASSIGN)) {
            advance();
            continue;
        }
        cout << "    Type: " << tokens[currentTokenIndex].getTokenTypeName()
             << ", Value: \"" << tokens[currentTokenIndex].value << "\"" << endl;

        advance();

        if (currentTokenIndex >= tokens.size()) {
            Error::throwError(ErrorCode::UNEXPECTED_END_IN_BLOCK);
        }

        if (checkCurrentTokenType(TOKENS::AND) || checkCurrentTokenType(TOKENS::OR)) {
            advance();

            if (currentTokenIndex >= tokens.size()) {
                Error::throwError(ErrorCode::UNEPECTED_END_LOGICAL_OP);
            }

            if (checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
                Error::throwError(ErrorCode::UNEPECTED_END_LOGICAL_OP);
            }
        }
    }

    if (!checkCurrentTokenType(TOKENS::CLOSE_PAREN)) {
        Error::throwError(ErrorCode::EXPECTED_CLOSE_PARENT);
    }

    parseBlock(statementType);
}