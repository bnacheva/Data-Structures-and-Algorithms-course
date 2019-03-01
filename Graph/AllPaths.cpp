#include<iostream>
#include <list>
using namespace std;

int cnt = 0;

class Graph
{
    int V;
    list<int> *adj;
    void printAllPathsUtil(int, int, bool [], int [], int &, int[], int);

public:
    Graph(int V);
    void addEdge(int u, int v);
    void printAllPaths(int s, int d, int arr[], int);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::printAllPaths(int s, int d, int arr[], int maxShops)
{
    bool *visited = new bool[V];

    int *path = new int[V];
    int path_index = 0;

    for (int i = 0; i < V; i++)
        visited[i] = false;

    printAllPathsUtil(s, d, visited, path, path_index, arr, maxShops);
}

void Graph::printAllPathsUtil(int u, int d, bool visited[],
                              int path[], int &path_index, int arr[], int maxShops)
{
    int sum = 0;
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    if (u == d)
    {
        for (int i = 0; i<path_index; i++)
        {
            sum += arr[path[i]];
        }
        if (sum <= maxShops)
        {
            cnt ++;
        }
    }
    else
    {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])
                printAllPathsUtil(*i, d, visited, path, path_index, arr, maxShops);
    }
    path_index--;
    visited[u] = false;
}

int main()
{
    int n; cin >> n;
    int maxShops; cin >> maxShops;
    int value;
    int arrValues[n];
    int counter = 0;
    Graph g(n);
    for (int i = 0; i < n; i++)
    {
        g.addEdge(0, i);
        cin >> value;
        arrValues[i] = value;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int startPos, endPos;
        cin >> startPos >> endPos;
        g.printAllPaths(startPos - 1, endPos - 1, arrValues, maxShops);
    }
    cout << cnt;

    return 0;
}
