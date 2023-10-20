#include "../../include/parser/parser_constructors.hpp"

ConstructorParser::ConstructorParser(const vector<Token> &tokens, int &currentIndex) : Parser(tokens, currentIndex) {}

void ConstructorParser::parseConstructor(const string &className)
{
    if (!hasConstructor(className)) {
        return;
    }

    cout << "    Parsing constructor : " + tokens[currentTokenIndex].value << endl;

    advance();
}

bool ConstructorParser::hasConstructor(const string &className) {
    return className == tokens[currentTokenIndex].value;
}