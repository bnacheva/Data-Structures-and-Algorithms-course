#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

template <class T>
struct elem_link
{
    T inf;
    elem_link<T> *link;
};

template <class T>
class LList
{
public:
    LList();
    ~LList();
    LList(const LList<T>&);
    LList<T>& operator=(const LList<T>&);

    void IterStart(elem_link<T> *p = NULL);
    elem_link<T>* Iter();

    void ToEnd(const T&);
    void InsertAfter(elem_link<T>*, const T&);
    void InsertBefore(elem_link<T>*, const T&);
    bool DeleteAfter(elem_link<T>*, T&);
    bool DeleteBefore(elem_link<T>*, T&);
    void DeleteElem(elem_link<T>*, T&);
    void print();
    int length();

    elem_link<T>* getStart()
    {
        return start;
    }

    elem_link<T>* getEnd()
    {
        return endL;
    }

private:
    elem_link<T> *start;
    elem_link<T> *current;
    elem_link<T> *endL;

    void DeleteList();
    void CopyList(const LList<T>&);
};

template <class T>
LList<T>::LList()
{
    start = NULL;
    endL = NULL;
}

template <class T>
LList<T>::~LList()
{
    DeleteList();
}

template <class T>
LList<T>::LList(const LList<T>& ll)
{
    CopyList(ll);
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& other)
{
    if (this != &other)
    {
        DeleteList();
        CopyList(other);
    }
    return *this;
}

template <class T>
void LList<T>::DeleteList()
{
    elem_link<T> *p;
    while(start)
    {
        p = start;
        start = start->link;
        delete p;
    }
    endL = NULL;
}

template <class T>
void LList<T>::CopyList(const LList<T>& ll)
{
    start = endL = NULL;
    if (ll.start)
    {
        elem_link<T> *p = ll.start;
        while(p)
        {
            ToEnd(p->inf);
            p = p->link;
        }
    }
}

template <class T>
void LList<T>::IterStart(elem_link<T> *p)
{
    if(p) p = current;
    else current = start;
}

template <class T>
elem_link<T>* LList<T>::Iter()
{
    elem_link<T> *p = current;
    if (current) current = current->link;
    return p;
}

template <class T>
void LList<T>::ToEnd(const T& x)
{
    current = endL;
    endL = new elem_link<T>;
    endL->inf = x;
    endL->link = NULL;
    if (current) current->link = endL;
    else start = endL;
}

template <class T>
void LList<T>::InsertAfter(elem_link<T> *p, const T& x)
{
    elem_link<T> *q = new elem_link<T>;
    q->inf = x;
    q->link = p->link;

    if (p == endL) endL = q;

    p->link = q;
}

template <class T>
void LList<T>::InsertBefore(elem_link<T> *p, const T& x)
{
    elem_link<T> *q = new elem_link<T>;
    *q = *p;

    if (p == endL) endL = q;
    p->inf = x;
    p->link = q;
}

template <class T>
bool LList<T>::DeleteAfter(elem_link<T> *p, T& x)
{
    if (p->link)
    {
        elem_link<T> *q = p->link;
        x = q->inf;
        p->link = q->link;

        if (q == endL) endL = p;
        delete q;
        return 1;
    }
    return 0;
}

template <class T>
void LList<T>::DeleteElem(elem_link<T> *p, T& x)
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
        elem_link<T> *q = start;
        while(q->link != p) q = q->link;
        DeleteAfter(q, x);
    }
}

template <class T>
bool LList<T>::DeleteBefore(elem_link<T> *p, T& x)
{
    if (p != start)
    {
        elem_link<T> *q = start;
        while(q->link != p) q = q->link;
        DeleteElem(q, x);
        return 1;
    }
    return 0;
}

template <class T>
void LList<T>::print()
{
    elem_link<T>* p = start;
    while(p)
    {
        cout << p->inf << " ";
        p = p->link;
    }
    cout << endl;
}

template <class T>
int LList<T>::length()
{
    int n = 0;
    elem_link<T>* p = start;
    while(p)
    {
        n++;
        p = p->link;
    }
    return n;
}

elem_link<long>* startPosition(elem_link<long> *head, long arr[], long p, LList<long>& intList)
{
    long index = 0;
    while (head != NULL && index < p)
    {
        if (head->inf == arr[index])
        {
            return head;
        }
        else
        {
            head = head->link;
            while (head != NULL)
            {
                if (head->inf == arr[index])
                {
                    return head;
                }
                head = head->link;
            }
        }
        index++;
        head = intList.getStart();
    }
    return NULL;
}

bool checkIsInside(long a, long b, LList<long>& intList)
{
    elem_link<long>* p = intList.getStart();
    elem_link<long>* q = p->link;
    while (p != NULL && q != NULL)
    {
        if ((p->inf == a && q->inf == b) || (p->inf == b && q->inf == a))
        {
            //intList.DeleteElem(p, a);
            return true;
        }
        p = p->link;
        q = q->link;
    }
    return false;
}

bool checkIsChecked(long a, long b, LList<long>& intList)
{
    elem_link<long>* p = intList.getStart();
    elem_link<long>* q = p->link;
    while (p != NULL && q != NULL)
    {
        if (p->inf == b && q->inf == a && a != b)
        {
            return false;
        }
        p = p->link;
        q = q->link;
    }
    return true;
}

bool equalElements(LList<long>& intList, long arr[], int n)
{
    int c1 = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            c1++;
        }
    }
    elem_link<long>* p = intList.getStart();
    bool flag = false;
    while (p != NULL)
    {
        if (p->inf == arr[0])
        {
            flag = true;
        }
        p = p->link;
        if (flag == false)
        {
            return false;
        }
    }
    if (c1 == n - 1 && flag == true)
    {
        return true;
    }
    return false;
}

int main()
{
    long n; cin>>n;
    if (n == 0 || n == 1)
    {
        cout<<0<<endl;
        return 0;
    }
    LList<long> intList;
    LList<long> checkedList;
    long number;
    for (long i = 0; i < n; i++)
    {
        cin>>number;
        intList.ToEnd(number);
    }
    long p; cin>>p;
    long arr[p];
    for (long i = 0; i < p; i++)
    {
        cin>>arr[i];
    }
    long counter = 0;
    for (long i = 0; i < p - 1; i++)
    {
        if (checkIsInside(arr[i], arr[i + 1], intList))
        {
            checkedList.ToEnd(arr[i]);
            checkedList.ToEnd(arr[i + 1]);
            if (checkIsChecked(arr[i], arr[i + 1], checkedList))
            {
                counter++;
            }
        }
    }
    if (equalElements(intList, arr, p))
    {
        cout<<1<<endl;
    }
    else
    {
        cout<<counter<<endl;
    }
    return 0;
}
