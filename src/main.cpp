#include "../include/parser.h"

int main() {
    string input = "if (x == 10) {y = 20} elseif (a != 1) {a = 17} elseif (xyz != 178) {xyz = 157}";
    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    parser parser(tokens);
    parser.parse();

    return 0;
}