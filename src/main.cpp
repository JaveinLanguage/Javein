#include "../include/parser.h"

int main() {
    string input = "if (x == 5 && y != 3) { x = 10 } elseif (y != 9 || a == 4) { y = 15 } elseif (z > 0) { z = 20 } else { z = 5 }";
    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    parser parser(tokens);
    parser.parse();

    return 0;
}