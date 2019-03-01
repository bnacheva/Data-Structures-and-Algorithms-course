#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

template <class T>
struct node
{
    T inf;
    node<T> *left;
    node<T> *right;
};

template <class T>
class BinOrdTree
{
private:
    node<T> *root;
    void DeleteTree(node<T>* &) const;
    void Copy(node<T>* &, node<T>* const&) const;
    void CopyTree(BinOrdTree<T> const&);
    void pr(const node<T> *) const;
    void Add(node<T> *&, T const &) const;

public:
    BinOrdTree();
    ~BinOrdTree();
    BinOrdTree(BinOrdTree<T> const&);
    BinOrdTree& operator=(BinOrdTree<T> const&);
    T RootTree() const;
    node<T>* GetRoot() const;
    BinOrdTree<T> LeftTree() const;
    BinOrdTree<T> RightTree() const;
    bool empty()const;
    void print() const;
    void AddNode(T const & x);
    void DeleteNode(T const&);
    void Create3(T, BinOrdTree<T>, BinOrdTree<T>);
    void Create();
    void CreateTree(T);
    void MinTree(T &, BinOrdTree<T> &) const;
    void averageOfLevels(node<T>*);
};

template <class T>
BinOrdTree<T>::BinOrdTree()
{
    root = NULL;
}
template <class T>
BinOrdTree<T>::~BinOrdTree()
{
    DeleteTree(root);
}

template <class T>
BinOrdTree<T>::BinOrdTree(BinOrdTree<T> const& r)
{
    CopyTree(r);
}
template <class T>
BinOrdTree<T>& BinOrdTree<T>::operator=(BinOrdTree<T> const& r)
{
    if (this != &r)
    {
        DeleteTree(root);
        CopyTree(r);
    }

    return *this;
}

template <class T>
void BinOrdTree<T>::DeleteTree(node<T>* &p) const
{
    if (p)
    {
        DeleteTree(p->left);
        DeleteTree(p->right);
        delete p;
        p = NULL;
    }
}

template <class T>
void BinOrdTree<T>::CopyTree(BinOrdTree<T> const& r)
{
    Copy(root, r.root);
}
template <class T>
void BinOrdTree<T>::Copy(node<T>* &pos, node<T>* const &r) const
{
    pos = NULL;
    if (r)
    {
        pos = new node<T>;
        pos->inf = r->inf;
        Copy(pos->left, r->left);
        Copy(pos->right, r->right);
    }
}

template <class T>
bool BinOrdTree<T>::empty()const
{
    return root == NULL;
}
template <class T>
T BinOrdTree<T>::RootTree()const
{
    return root->inf;
}
template <class T>
node<T>* BinOrdTree<T>::GetRoot() const
{
    return root;
}

template <class T>
BinOrdTree<T> BinOrdTree<T>::LeftTree() const
{
    BinOrdTree<T> t;
    Copy(t.root, root->left);
    return t;
}
template <class T>
BinOrdTree<T> BinOrdTree<T>::RightTree() const
{
    BinOrdTree<T> t;
    Copy(t.root, root->right);
    return t;
}

template <class T>
void BinOrdTree<T>::pr(const node<T>*p) const
{
    if (p)
    {
        pr(p->left);
        cout << p->inf << " ";
        pr(p->right);
    }
}
template <class T>
void BinOrdTree<T>::print() const
{
    pr(root);
}

template <class T>
void BinOrdTree<T>::Add(node<T>* &p, T const & x)const
{
    if (!p)
    {
        p = new node<T>;
        p->inf = x;
        p->left = NULL;
        p->right = NULL;
    }
    else if (x < p->inf)
        Add(p->left, x);
    else
        Add(p->right, x);
}

template <class T>
void BinOrdTree<T>::AddNode(T const & x)
{
    Add(root, x);
}

template <class T>
void BinOrdTree<T>::Create()
{
    root = NULL;
    T x;
    char c;
    do
    {
        cin >> x;
        AddNode(x);
        cout << "next elem y/n? ";
        cin >> c;
    }
    while (c == 'y');
}

template <class T>
void BinOrdTree<T>::CreateTree(T n)
{
    root = NULL;
    T x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        AddNode(x);
    }
}

template <class T>
void BinOrdTree<T>::Create3(T x, BinOrdTree<T> l, BinOrdTree<T> r)
{
    root = new node<T>;
    root->inf = x;
    Copy(root->left, l.root);
    Copy(root->right, r.root);
}

template <class T>
void BinOrdTree<T>::MinTree(T &x, BinOrdTree<T> &mint) const
{
    T a = RootTree();
    if (!root->left)
    {
        x = a;
        mint = RightTree();
    }
    else
    {
        BinOrdTree<T> t1;
        LeftTree().MinTree(x, t1);
        mint.Create3(a, t1, RightTree());
    }
}

template <class T>
void BinOrdTree<T>::DeleteNode(T const& x)
{
    if (root)
    {
        T a = RootTree();
        BinOrdTree<T> t;
        if (a == x && !root->left)
            *this = RightTree();
        else if (a == x && !root->right)
            *this = LeftTree();
        else if (a == x)
        {
            T c;
            RightTree().MinTree(c, t);
            Create3(c, LeftTree(), t);
        }
        else if (x < a)
        {
            t = *this;
            *this = LeftTree();
            DeleteNode(x);
            Create3(a, *this, t.RightTree());
        }
        else if (x > a)
        {
            t = *this;
            *this = RightTree();
            DeleteNode(x);
            Create3(a, t.LeftTree(), *this);
        }
    }
}

template <class T>
void BinOrdTree<T>::averageOfLevels(node<T>* r)
{
    vector<float> res;
    queue<node<T>*> q;
    q.push(r);

    while (!q.empty())
    {

        int sum = 0, count = 0;
        queue<node<T>*> temp;
        while (!q.empty())
        {
            node<T>* n = q.front();
            q.pop();
            sum += n->inf;
            count++;
            if (n->left != NULL)
                temp.push(n->left);
            if (n->right != NULL)
                temp.push(n->right);
        }
        q = temp;
        cout << fixed << setprecision(2) << (sum * 1.0 / count) << endl;
    }
}
int main()
{
    BinOrdTree<int> tree;
    int n; cin >> n;
    tree.CreateTree(n);
    tree.averageOfLevels(tree.GetRoot());
    return 0;
}
