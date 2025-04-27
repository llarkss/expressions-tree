#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <vector>
#include "ExpressionTree.h"

using namespace std;

TreeNode::TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}

ExpressionTree::ExpressionTree() : rootNode(nullptr) {}

ExpressionTree::~ExpressionTree()
{
    freeTree(rootNode);
}

bool ExpressionTree::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int ExpressionTree::getPriority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void ExpressionTree::createTree()
{
    if (rootNode != nullptr)
    {
        freeTree(rootNode);
        rootNode = nullptr;
    }

    string expression;
    cout << "Введите арифметическое выражение: ";
    cin.ignore();
    getline(cin, expression);

    rootNode = buildExpressionTree(expression);
    cout << "Дерево создано успешно!" << endl;
}

TreeNode* ExpressionTree::buildExpressionTree(const string& expression)
{
    stack<char> operators;
    vector<string> postfix;
    string number = "";

    //from regural form to RPN
    for (size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (c == ' ')
            continue;

        if (isdigit(c))
        {
            number += c;
        }
        else
        {
            if (!number.empty())
            {
                postfix.push_back(number);
                number = "";
            }

            if (c == '(')
            {
                operators.push(c);
            }
            else if (c == ')')
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    postfix.push_back(string(1, operators.top()));
                    operators.pop();
                }
                if (!operators.empty())
                {
                    operators.pop();
                }
            }
            else if (isOperator(c))
            {
                while (!operators.empty() && operators.top() != '(' &&
                    getPriority(operators.top()) >= getPriority(c))
                {
                    postfix.push_back(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(c);
            }
        }
    }

    if (!number.empty())
    {
        postfix.push_back(number);
    }

    while (!operators.empty())
    {
        postfix.push_back(string(1, operators.top()));
        operators.pop();
    }

    //from RPN to binary tree
    stack<TreeNode*> nodeStack;
    for (const string& token : postfix)
    {
        if (token.length() == 1 && isOperator(token[0]))
        {
            TreeNode* node = new TreeNode(token);
            if (!nodeStack.empty())
            {
                node->right = nodeStack.top();
                nodeStack.pop();
            }
            if (!nodeStack.empty())
            {
                node->left = nodeStack.top();
                nodeStack.pop();
            }
            nodeStack.push(node);
        }
        else
        {
            nodeStack.push(new TreeNode(token));
        }
    }

    return nodeStack.empty() ? nullptr : nodeStack.top();
}


void ExpressionTree::inOrder(TreeNode* root , int level )
{
    if (root == nullptr)
    {
        return;
    }

    string indent(level * 4, ' ');

    cout << indent << "Значение: " << root->value
         << ", Адрес: " << root
         << ", Левый потомок: " << root->left
         << ", Правый потомок: " << root->right << endl;

    inOrder(root->left, level + 1);
    inOrder(root->right, level + 1);
}

void ExpressionTree::printTree()
{
    if (rootNode == nullptr)
    {
        std::cout << "Дерево пусто. Сначала создайте дерево." << std::endl;
        return;
    }

    inOrder(rootNode, 0); 
}

TreeNode* ExpressionTree::findNode(TreeNode* root, const string& value)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->value == value)
    {
        return root;
    }

    TreeNode* leftResult = findNode(root->left, value);
    if (leftResult != nullptr)
    {
        return leftResult;
    }

    return findNode(root->right, value);
}

void ExpressionTree::searchNode()
{
    if (rootNode == nullptr)
    {
        cout << "Дерево пусто. Сначала создайте дерево." << endl;
        return;
    }

    string value;
    cout << "Введите значение для поиска: ";
    cin >> value;

    TreeNode* foundNode = findNode(rootNode, value);
    if (foundNode)
    {
        cout << "Узел с значением '" << value << "' найден по адресу: " << foundNode
             << ", Левый потомок: "  << foundNode->left
             << ", Правый потомок: " << foundNode->right << endl;
    }
    else
    {
        cout << "Узел с значением '" << value << "' не найден" << endl;
    }
}

int ExpressionTree::countNodes(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int ExpressionTree::treeHeight(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return 1 + max(leftHeight, rightHeight);
}

void ExpressionTree::treeInfo()
{
    if (rootNode == nullptr)
    {
        cout << "Дерево пусто. Сначала создайте дерево." << endl;
        return;
    }

    cout << "Количество узлов в дереве: " << countNodes(rootNode) << endl;
    cout << "Высота дерева: " << treeHeight(rootNode) << endl;
}

double ExpressionTree::evaluateExpression(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr)
    {
        return stod(node->value);
    }

    double leftValue = evaluateExpression(node->left);
    double rightValue = evaluateExpression(node->right);

    if (node->value == "+")
    {
        return leftValue + rightValue;
    }
    else if (node->value == "-")
    {
        return leftValue - rightValue;
    }
    else if (node->value == "*")
    {
        return leftValue * rightValue;
    }
    else if (node->value == "/")
    {
        if (rightValue == 0)
        {
            cout << "Ошибка: деление на ноль!" << endl;
            return 0;
        }
        return leftValue / rightValue;
    }

    return 0;
}

void ExpressionTree::calculateResult()
{
    if (rootNode == nullptr)
    {
        cout << "Дерево пусто. Сначала создайте дерево." << endl;
        return;
    }

    double result = evaluateExpression(rootNode);
    cout << "Результат вычисления выражения: " << result << endl;
}

void ExpressionTree::freeTree(TreeNode* root)
{
    if (root == nullptr)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

void ExpressionTree::freeMemory()
{
    freeTree(rootNode);
    rootNode = nullptr;
}
