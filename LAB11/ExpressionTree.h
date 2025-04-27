#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <string>

struct TreeNode
{
    std::string value;        
    TreeNode* left;            
    TreeNode* right;           

   
    TreeNode(std::string val);
};

class ExpressionTree
{
public:
private:
    TreeNode* rootNode; 
    
    
    TreeNode* buildExpressionTree(const std::string& expression);
    bool isOperator(char c);
    int getPriority(char op);
    double evaluateExpression(TreeNode* node);
    
    int treeHeight(TreeNode* root);
    int countNodes(TreeNode* root);
    TreeNode* findNode(TreeNode* root, const std::string& value);
    void inOrder(TreeNode* root , int level = 0);

public:

    void freeMemory();
    void freeTree(TreeNode* root);
    ExpressionTree();
    ~ExpressionTree();

    void createTree();
    void searchNode();
    void treeInfo();
    void calculateResult();
    void printTree();
};

#endif 
