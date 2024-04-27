#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

class TreeNode
{
public:
    string value;
    TreeNode* left_child;
    TreeNode* right_child;

    TreeNode(string data)
    {
        value = data;
        left_child = NULL;
        right_child = NULL;
    }

    ~TreeNode()
    {
        delete left_child;
        delete right_child;
    }
};

class ExpressionTree
{
public:
    TreeNode* root;

    ExpressionTree()
    {
        root = NULL;
    }

    ~ExpressionTree()
    {
        delete root;
    }

    double evaluate()
    {
        return evaluateExpression(root);
    }

    double evaluateExpression(TreeNode* current_node)
    {
        if (current_node->left_child == NULL && current_node->right_child == NULL)
        {
            return stod(current_node->value);
        }
        else
        {
            string operator_symbol = current_node->value;
            if (operator_symbol == "+")
            {
                return evaluateExpression(current_node->left_child) + evaluateExpression(current_node->right_child);
            }
            if (operator_symbol == "-")
            {
                return evaluateExpression(current_node->left_child) - evaluateExpression(current_node->right_child);
            }
            if (operator_symbol == "*")
            {
                return evaluateExpression(current_node->left_child) * evaluateExpression(current_node->right_child);
            }
            else
            {
                return evaluateExpression(current_node->left_child) / evaluateExpression(current_node->right_child);
            }
        }
    }

    void build(string expression)
    {
        root = constructExpressionTree(expression);
    }

    TreeNode* constructExpressionTree(string expression)
    {
        stack<int> brackets_stack;
        vector<int> operator_positions;
        string cleaned_expression = removeOuterBrackets(expression);
        int length = cleaned_expression.length();
        for (int i = 0; i < length; i++)
        {
            char current_char = cleaned_expression[i];
            if (current_char == '(')
            {
                brackets_stack.push(i);
            }
            else if (current_char == ')')
            {
                brackets_stack.pop();
            }
            else if (brackets_stack.empty() && (current_char == '+' || current_char == '-' || current_char == '*' || current_char == '/'))
            {
                operator_positions.push_back(i);
            }
        }
        int operator_position;
        if (operator_positions.empty())
        {
            return new TreeNode(cleaned_expression);
        }
        else if (operator_positions.size() == 1)
        {
            operator_position = operator_positions.at(0);
        }
        else
        {
            int operator_index = findLowestPrecedenceOperator(cleaned_expression, operator_positions);
            operator_position = operator_positions.at(operator_index);
        }
        TreeNode* node = new TreeNode(cleaned_expression.substr(operator_position, 1));
        node->left_child = constructExpressionTree(cleaned_expression.substr(0, operator_position));
        node->right_child = constructExpressionTree(cleaned_expression.substr(operator_position + 1, length - operator_position - 1));
        return node;
    }

    string removeOuterBrackets(string expression)
    {
        stack<int> brackets_stack;
        int length = expression.length();
        for (int i = 0; i < length - 1; i++)
        {
            char current_char = expression[i];
            if (current_char == '(')
            {
                brackets_stack.push(i);
            }
            else if (current_char == ')')
            {
                brackets_stack.pop();
            }
        }
        if (brackets_stack.size() == 1 && brackets_stack.top() == 0)
        {
            return expression.substr(1, length - 2);
        }
        return expression;
    }

    int findLowestPrecedenceOperator(string expression, vector<int> operator_positions)
    {
        for (char operator_symbol : {'-', '+', '*', '/'})
        {
            for (int i = 0; i < operator_positions.size(); i++)
            {
                if (expression[operator_positions.at(i)] == operator_symbol)
                {
                    return i;
                }
            }
        }
    }

    void traverse()
    {
        traverseExpression(root);
    }

    void traverseExpression(TreeNode* root)
    {
        if (!root)
        {
            return;
        }
        cout << "(";
        traverseExpression(root->left_child);
        cout << root->value;
        traverseExpression(root->right_child);
        cout << ")";
    }

    int calculateHeight(TreeNode* root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return 1 + max(calculateHeight(root->left_child), calculateHeight(root->right_child));
    }

    int getColumnCount(int height)
    {
        if (height == 1)
        {
            return 1;
        }
        return getColumnCount(height - 1) + getColumnCount(height - 1) + 1;
    }

    void fillMatrix(string** matrix, TreeNode* root, int column, int row, int height)
    {
        if (root == NULL)
        {
            return;
        }
        matrix[row][column] = root->value;
        fillMatrix(matrix, root->left_child, column - pow(2, height - 2), row + 1, height - 1);
        fillMatrix(matrix, root->right_child, column + pow(2, height - 2), row + 1, height - 1);
    }

    void printExpressionTree()
    {
        int height = calculateHeight(root);
        int column_count = getColumnCount(height);
        string** matrix = new string * [height];
        for (int i = 0; i < height; i++)
        {
            matrix[i] = new string[column_count];
        }
        fillMatrix(matrix, root, column_count / 2, 0, height);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < column_count; j++)
            {
                if (matrix[i][j] == "")
                {
                    cout << " ";
                }
                else
                {
                    cout << matrix[i][j];
                }
            }
            cout << endl;
        }
    }
};


int main()
{
    ExpressionTree* expression_tree = new ExpressionTree();
    string expression = "((13-9)+42)";
    expression_tree->build(expression);
    cout << "Expression tree:" << endl;
    expression_tree->printExpressionTree();
    cout << endl;
    cout << "Result: " << expression_tree->evaluate() << endl;
    cout << endl;
    return 0;
}
