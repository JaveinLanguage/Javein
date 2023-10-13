#include "../include/parser.h"

int main() {
    string input = "if (x == 5) { x = 10 } elseif (y != 9) { y = 15 }";
    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    parser parser(tokens);
    parser.parse();

    return 0;
}