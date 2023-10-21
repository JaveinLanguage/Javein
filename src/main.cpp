#include "../include/parser.hpp"

int main()
{
    string input = "class Player() {"
                   "  string name"
                   "  int age"
                   ""
                   "  Player(string name, int age) {"
                   "    this.name = name"
                   "    this.age = age"
                   "  }"
                   ""
                   "  fn int getPlr() {"
                   "    rn 1"
                   "  }"
                   "}";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    int currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}