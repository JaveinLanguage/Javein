#include "../include/parser.hpp"

int main()
{
    string input = "fn int getAge(string x, int a = 10) "
                   "  rn 10"
                   "}"
                   "if (x > 10) {"
                   "  x = 15"
                   "}";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    int currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}