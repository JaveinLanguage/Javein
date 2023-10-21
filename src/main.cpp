#include "../include/parser.hpp"

int main()
{
    string input = "int a = 10";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    int currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}