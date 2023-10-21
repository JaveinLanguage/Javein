#ifndef JAVEIN_PARSER_VARIABLES_HPP
#define JAVEIN_PARSER_VARIABLES_HPP

#include "../parser.hpp"

class VariablesParser : public Parser
{
public:
    explicit VariablesParser(const vector<Token> &tokens, int &currentIndex);
    void parseVariableStatement();
    void printAST();

private:
    vector<unique_ptr<ASTNode>> astNodes;
};

#endif
