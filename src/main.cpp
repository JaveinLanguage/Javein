#include "../include/parser.hpp"

int main()
{
    string input = "  fn int getAge() {"
                   "    return 10"
                   "  }";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    size_t currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}