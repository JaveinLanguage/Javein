#include "include/lexer/Lexer.h"
#include <iostream>

using namespace std;

int main() 
{
    string input = "12 + 34 - 56 * 78 / 90 + (2 + 2)";
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        cout << "[ ";
        switch (token.type) {
        case TOKENS::INT: cout << "INT"; break;
        case TOKENS::PLUS: cout << "PLUS"; break;
        case TOKENS::MINUS: cout << "MINUS"; break;
        case TOKENS::MUL: cout << "MULTIPLY"; break;
        case TOKENS::DIV: cout << "DIVIDE"; break;
        case TOKENS::LPAREN: cout << "LPAREN"; break;
        case TOKENS::RPAREN: cout << "RPAREN"; break;
        case TOKENS::END: cout << "END"; break;
        case TOKENS::INVALID: cout << "INVALID"; break;
        }
        cout << ", " << token.value << "]" << "\n";
    }

    return 0;
}
