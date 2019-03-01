#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Node
{
    double value;
    Node *left;
    Node *right;
    int height;

    Node(double value, Node *left, Node *right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
        this->height = 0;
    }
};

class AVLTree
{
public:

    bool containsRecursive(Node *current, double value)
    {
        if (current == NULL)
        {
            return false;
        }

        if (current->value == value)
        {
            return true;
        }

        if (value < current->value)
        {
            return containsRecursive(current->left, value);
        }
        else
        {
            return containsRecursive(current->right, value);
        }
    }

    void printRecursive(Node *current)
    {
        if (current == NULL)
        {
            return;
        }

        printRecursive(current->left);
        cout << current->value << " ";
        printRecursive(current->right);
    }

    AVLTree()
    {
    }
    
    int height(Node* p) 
    { 
        if (p == NULL) 
        {
            return 0; 
        }
        return p->height; 
    } 
    
    Node *rightRotate(Node *y) 
    { 
        Node *x = y->left; 
        Node *T2 = x->right; 

        x->right = y; 
        y->left = T2; 

        y->height = std::max(height(y->left), height(y->right))+1; 
        x->height = std::max(height(x->left), height(x->right))+1; 

        return x; 
    } 

    Node *leftRotate(Node *x) 
    { 
        Node *y = x->right; 
        Node *T2 = y->left; 

        y->left = x; 
        x->right = T2; 

        x->height = std::max(height(x->left), height(x->right))+1; 
        y->height = std::max(height(y->left), height(y->right))+1; 

        return y; 
    } 

    int getBalance(Node* p) 
    { 
        if (p == NULL)
        {
            return 0;
        }
        return height(p->left) - height(p->right); 
    } 
    
    Node* add(Node* root, double value) 
    { 
        if (root == NULL)
        {
            return new Node(value, NULL, NULL);
        }

        if (value < root->value)
        {
            root->left  = add(root->left, value); 
        }
        else if (value > root->value) 
        {
            root->right = add(root->right, value); 
        }

        root->height = 1 + std::max(height(root->left), height(root->right)); 

        int balance = getBalance(root); 

        if (balance > 1 && value < root->left->value)
        {
            root = rightRotate(root); 
            return root;
        }

        if (balance < -1 && value > root->right->value) 
        {
            root = leftRotate(root); 
            return root;
        }      

        if (balance > 1 && value > root->left->value) 
        { 
            root->left =  leftRotate(root->left); 
            root = rightRotate(root); 
            return root;
        } 

        if (balance < -1 && value < root->right->value) 
        { 
            root->right = rightRotate(root->right); 
            root = leftRotate(root); 
            return root;
        } 

        return root; 
    } 
    
    Node* minValue(Node* root)
    {
        Node* current = root;
        
        while(current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }
    
    Node* remove(Node* root, double value) 
    {  
        if (root == NULL)
        {
            return root; 
        }      
        if (value < root->value) 
        {
            root->left = remove(root->left, value); 
        }    
        else if(value > root->value)
        {
            root->right = remove(root->right, value); 
        }     
        else
        { 
            if((root->left == NULL) || (root->right == NULL)) 
            { 
                Node *temp = root->left ? root->left : root->right; 

                if (temp == NULL) 
                { 
                    temp = root; 
                    root = NULL; 
                } 
                else
                {
                    *root = *temp;   
                } 
            } 
            else
            {  
                Node* temp = minValue(root->right); 

                root->value = temp->value; 

                root->right = remove(root->right, temp->value); 
            } 
        } 
        if (root == NULL)
        {
            return root;
        }      
        root->height = 1 + std::max(height(root->left), height(root->right)); 

        int balance = getBalance(root); 

        if (balance > 1 && getBalance(root->left) > 0)
        {
            root = rightRotate(root);
            return root;
        }

        if (balance > 1 && getBalance(root->left) < 0) 
        { 
            root->left = leftRotate(root->left); 
            root = rightRotate(root); 
            return root;
        } 

        if (balance < -1 && getBalance(root->right) <= 0)
        {
            root = leftRotate(root);
            return root;
        } 
            
        if (balance < -1 && getBalance(root->right) > 0) 
        { 
            root->right = rightRotate(root->right); 
            root = leftRotate(root); 
            return root;
        } 

        return root; 
    } 

    bool contains(Node* root, double value)
    {
        if (root == NULL)
        {
            return false;
        }

        return containsRecursive(root, value);
    }

    void print(Node* root)
    {
        if (root == NULL)
        {
            return;
        }

        printRecursive(root);
        cout << endl;
    }
};

int main()
{
    AVLTree tree;
    Node *root = NULL; 
    string operation;
    double number;
    int N;

    cin >> N;
    cout << fixed;
    
    bool first = false;

    for (size_t i = 0; i < N; i++)
    {
        cin >> operation;
        if (operation != "print")
        {
            cin >> number;
        }

        if (operation == "add")
        {
            if(tree.contains(root, number))
            {
                cout << number << " already added" << endl;
            }
            else
            {
                root = tree.add(root, number);
            }
        }
        else if (operation == "remove")
        {
            if(!tree.contains(root, number))
            {
                cout << number << " not found to remove" << endl;
            }
            else
            {
                root = tree.remove(root, number);
            }
            
        }
        else if (operation == "contains")
        {
            if (tree.contains(root, number))
            {
                cout << "yes" << endl;
            }
            else
            {
                cout << "no" << endl;
            }
        }
        else if (operation == "print")
        {
            tree.print(root);
        }
    }

    return 0;
}
