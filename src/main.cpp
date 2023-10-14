#include "../include/parser.hpp"

int main()
{
    string input = "int i = 10"
                   "string str = \"AHAH\""
                   "float flt = 10.2"
                   "char c = 'c'"
                   "boolean bool = true"
                   "if (a > 4 && r == 48) {"
                   "    boolean result = true"
                   "} elseif (t == 4) {"
                   "    t += 4;"
                   "} else {"
                   "    r == 48"
                   "}"
                   "for (int i = 0; i > 0; i++) {"
                   "    i = 10"
                   "}"
                   "fn int bast(char c = 'a', float wow = 10.2) {"
                   "    a = 10"
                   "    return a"
                   "}";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    size_t currentTokenIndex = 0;

    Parser parser(tokens, currentTokenIndex);
    parser.parse();

    return 0;
}