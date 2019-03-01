#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

struct elem_link
{
    int inf;
    elem_link *link;
};

class LList
{
public:
    LList();
    ~LList();
    LList(const LList&);
    LList& operator=(const LList&);

    void IterStart(elem_link *p = NULL);
    elem_link* Iter();

    void ToEnd(const int&);
    void InsertAfter(elem_link*, const int&);
    void InsertBefore(elem_link*, const int&);
    bool DeleteAfter(elem_link*, int&);
    bool DeleteBefore(elem_link*, int&);
    void DeleteElem(elem_link*, int&);
    void print();
    int length();

    elem_link* getStart()
    {
        return start;
    }

    elem_link* getEnd()
    {
        return endL;
    }

private:
    elem_link *start;
    elem_link *current;
    elem_link *endL;

    void DeleteList();
    void CopyList(const LList&);
};

LList::LList()
{
    start = NULL;
    endL = NULL;
}

LList::~LList()
{
    DeleteList();
}

LList::LList(const LList& ll)
{
    CopyList(ll);
}

LList& LList::operator=(const LList& other)
{
    if (this != &other)
    {
        DeleteList();
        CopyList(other);
    }
    return *this;
}

void LList::DeleteList()
{
    elem_link *p;
    while(start)
    {
        p = start;
        start = start->link;
        delete p;
    }
    endL = NULL;
}

void LList::CopyList(const LList& ll)
{
    start = endL = NULL;
    if (ll.start)
    {
        elem_link *p = ll.start;
        while(p)
        {
            ToEnd(p->inf);
            p = p->link;
        }
    }
}

void LList::IterStart(elem_link *p)
{
    if(p) p = current;
    else current = start;
}

elem_link* LList::Iter()
{
    elem_link *p = current;
    if (current) current = current->link;
    return p;
}

void LList::ToEnd(const int& x)
{
    current = endL;
    endL = new elem_link;
    endL->inf = x;
    endL->link = NULL;
    if (current) current->link = endL;
    else start = endL;
}

void LList::InsertAfter(elem_link *p, const int& x)
{
    elem_link *q = new elem_link;
    q->inf = x;
    q->link = p->link;

    if (p == endL) endL = q;

    p->link = q;
}

void LList::InsertBefore(elem_link *p, const int& x)
{
    elem_link *q = new elem_link;
    *q = *p;

    if (p == endL) endL = q;
    p->inf = x;
    p->link = q;
}

bool LList::DeleteAfter(elem_link *p, int& x)
{
    if (p->link)
    {
        elem_link *q = p->link;
        x = q->inf;
        p->link = q->link;

        if (q == endL) endL = p;
        delete q;
        return 1;
    }
    return 0;
}

void LList::DeleteElem(elem_link *p, int& x)
{
    if (p == start)
    {
        x = p->inf;
        if (start == endL)
        {
            start = endL = NULL;
        }
        else start = start->link;
        delete p;
    }
    else
    {
        elem_link *q = start;
        while(q->link != p) q = q->link;
        DeleteAfter(q, x);
    }
}

bool LList::DeleteBefore(elem_link *p, int& x)
{
    if (p != start)
    {
        elem_link *q = start;
        while(q->link != p) q = q->link;
        DeleteElem(q, x);
        return 1;
    }
    return 0;
}

void LList::print()
{
    elem_link* p = start;
    while(p)
    {
        cout << p->inf << " ";
        p = p->link;
    }
    cout << endl;
}

int LList::length()
{
    int n = 0;
    elem_link* p = start;
    while(p)
    {
        n++;
        p = p->link;
    }
    return n;
}

int sumElements(elem_link *p)
{
    int sum = 0;
    while (p != NULL)
    {
        sum += p->inf;
        p = p->link;
    }
    return sum;
}

int main()
{
    int n; cin>>n;
    int sum = 0;
    LList listSums;
    int arrP[n];
    int arrM[n];
    int p;
    int m;
    for (int i = 0; i < n; i++)
    {
        int p2 = p;
        int m2 = m;
        cin>>p>>m;
        arrP[i] = p;
        arrM[i] = m;
        if (arrM[i] == 0 && arrP[i] < arrP[i - 1])
        {
            listSums.ToEnd(0);
        }
        else if (p == p2)
        {
            listSums.ToEnd(m);
        }
        else if (m == 0)
        {
            sum -= m2;
            listSums.ToEnd(sum);
        }
        else
        {
            sum += m;
            listSums.ToEnd(sum);
        }
    }
    elem_link *head = listSums.getStart();
    cout<<sumElements(head)<<endl;
    return 0;
}
