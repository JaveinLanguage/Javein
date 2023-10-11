#include "../include/lexer.h"
#include "../include/parser.h"

using namespace std;

int main() 
{
    string input = "if (x == 10) { y = 20; } else if (x > 5) { y = 15; } else { y = 5; }";
    lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.parse();

    return 0;
}
