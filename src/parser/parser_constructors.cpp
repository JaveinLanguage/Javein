#include "../../include/parser/parser_constructors.hpp"

ConstructorParser::ConstructorParser(const vector<Token> &tokens, size_t &currentTokenIndex) : Parser(tokens, currentTokenIndex) {}



size_t ConstructorParser::parseConstructor(const string &className)
{
    if (!hasConstructor(className)) {
        return currentTokenIndex;
    }

    cout << "    Parsing constructor : " + tokens[currentTokenIndex].value << endl;

    advance();



    return currentTokenIndex;
}

bool ConstructorParser::hasConstructor(const string &className) {
    return className == tokens[currentTokenIndex].value;
}