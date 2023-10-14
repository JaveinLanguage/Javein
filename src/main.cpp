#include "../include/parser.hpp"

int main() {
    string input = "if (a > 4 && r == 48) {"
                   "    int result = a + b"
                   "} elseif (t == 4) {"
                   "    t += 4;"
                   "} else {"
                   "    r == 48"
                   "}"
                   "for (int i = 0; i > 0; i++) {"
                   "    i = 10"
                   "}";

    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    size_t currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}