#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
};

void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
};


//the leftmost leaf
struct node *minValueNode(node *nodeToDel)
{
    node *current = nodeToDel;
    while (current->left != NULL)
        current = current->left;
    return current;
};

struct node *deleteNode(struct node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);
        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
};

void printPostorder(struct node* node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    printPostorder(node->left);

    // then recur on right subtree
    printPostorder(node->right);

    // now deal with the node
    cout << node->key << " ";
}

void printInorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    printInorder(node->left);

    /* then print the data of node */
    cout << node->key << " ";

    /* now recur on right child */
    printInorder(node->right);
}

void printPreorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first print data of node */
    cout << node->key << " ";

    /* then recur on left sutree */
    printPreorder(node->left);

    /* now recur on right subtree */
    printPreorder(node->right);
}

void sumOfLeafs(node *root, int *sum)
{
    if(!root)
        return;
    if (!root->left && !root->right)
        *sum += root->key;
    sumOfLeafs(root->left, sum);
    sumOfLeafs(root->right, sum);
}

int height(node* root)
{
    if (root == NULL)
    {
        return -1;
    }

    int left = height(root->left);
    int right = height(root->right);

    return 1 + std::max(left, right);
}

bool isLeaf(node* node)
{
    if (node == NULL)
        return false;
    if (node->left == NULL && node->right == NULL)
        return true;
    return false;
}

int leftLeavesSum(node* root)
{
    int sum = 0;
    if (root != NULL)
    {
        if (isLeaf(root->left))
        {
            sum += root->left->key;
        }
        else
        {
            sum += leftLeavesSum(root->left);
        }
        sum += leftLeavesSum(root->right);
    }
    return sum;
}

int rightLeavesSum(node* root)
{
    int sum = 0;
    if (root != NULL)
    {
        if (isLeaf(root->left))
        {
            sum += root->right->key;
        }
        else
        {
            sum += rightLeavesSum(root->right);
        }
        sum += rightLeavesSum(root->left);
    }
}

int main()
{
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    //inOrder(root);
    //cout << endl;
    //deleteNode(root, 30);
    //inOrder(root);
    cout << height(root) << endl;
    cout << leftLeavesSum(root) << endl;
    cout << rightLeavesSum(root) << endl;
    printPreorder(root);
    cout << endl;
    printInorder(root);
    cout << endl;
    printPostorder(root);
    cout << endl;

    node *root1 = newNode(1);
    root1->left = newNode(2);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);
    root1->right = newNode(3);
    root1->right->right = newNode(7);
    root1->right->left = newNode(6);
    root1->right->left->right = newNode(8);

    // variable to store sum of leaf nodes
    int sum = 0;
    sumOfLeafs(root1, &sum);
    cout << sum << endl;
    return 0;
}
