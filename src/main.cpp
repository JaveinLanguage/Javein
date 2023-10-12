#include "../include/lexer.h"
#include "../include/parser.h"

int main() {
    string input = "if (x == 10) { y = 20 }";
    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    return 0;
}