#include "../include/parser.hpp"

int main()
{
    string input = "class aClass(string name, int age) {"
                   "  string name"
                   "  int age"
                   ""
                   "  aClass(string name, int age) {"
                   "    this.name = name"
                   "    this.age = age"
                   "  }"
                   ""
                   "  fn string getName() {"
                   "    return this.name"
                   "  }"
                   ""
                   "  fn age getAge() {"
                   "    return this.age"
                   "  }"
                   "}";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    size_t currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}