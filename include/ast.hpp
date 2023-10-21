#ifndef JAVEIN_AST_HPP
#define JAVEIN_AST_HPP

#include <iostream>
#include <memory>

class ASTNode;
class VariableDeclarationNode;

class ASTNode
{
public:
    virtual ~ASTNode() = default;
    virtual void print(int level = 0) const = 0;
};

inline void printIndent(int level) {
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
}

class VariableDeclarationNode : public ASTNode
{
    string type;
    string name;
    string value;

public:
    VariableDeclarationNode(const string &t, const string &n, const string &v)
            : type(t), name(n), value(v) {}

    void print(int level = 0) const override {
        printIndent(level);
        cout << "VariableDeclarationNode" << std::endl;

        printIndent(level + 1);
        cout << "Type: " << type << std::endl;

        printIndent(level + 1);
        cout << "Name: " << name << std::endl;

        printIndent(level + 1);
        cout << "Value: " << value << std::endl;
    }
};

#endif