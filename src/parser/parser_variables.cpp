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

    string variableType = tokens[currentTokenIndex].getTokenTypeName();
    advance();

    if (!checkCurrentTokenType(TOKENS::ID)) {
        Error::throwError(ErrorCode::EXPECTED_ID);
    }

    string variableName = tokens[currentTokenIndex].value;
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

    string variableValue = tokens[currentTokenIndex].value;

    unique_ptr<VariableDeclarationNode> variableNode = make_unique<VariableDeclarationNode>(variableType, variableName, variableValue);
    astNodes.push_back(std::move(variableNode));

    printAST();
    advance();
}

void VariablesParser::printAST() {
    cout << "Printing AST:" << endl;

    for (const auto& node : astNodes) {
        node->print();
    }
}
