#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#define NINF INT_MIN
using namespace std;

class Node
{
    int v;
    int weight;

public:
    Node(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};

class Graph
{
    int V;
    list<Node>* nodes;
    void topologicalSort(int v, bool visited[], stack<int>& Stack);

public:
    Graph(int V);
    void addEdge(int u, int v, int weight);
    int longestPath(int s, int t);
};

Graph::Graph(int V)
{
    this->V = V;
    nodes = new list<Node>[V];
}

void Graph::addEdge(int u, int v, int weight)
{
    Node node(v, weight);
    nodes[u].push_back(node);
}

void Graph::topologicalSort(int v, bool visited[], stack<int>& Stack)
{
    visited[v] = true;
    list<Node>::iterator i;
    for (i = nodes[v].begin(); i != nodes[v].end(); ++i)
    {
        Node node = *i;
        if (!visited[node.getV()])
            topologicalSort(node.getV(), visited, Stack);
    }
    Stack.push(v);
}

int Graph::longestPath(int s, int t)
{
    stack<int> Stack;
    int dist[V];
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSort(i, visited, Stack);

    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    while (Stack.empty() == false)
    {
        int u = Stack.top();
        Stack.pop();

        list<Node>::iterator i;
        if (dist[u] != NINF)
        {
            for (i = nodes[u].begin(); i != nodes[u].end(); ++i)
                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    return (dist[t] == NINF) ? -1 : dist[t];
}

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph g(n);
    for(int i = 0; i < m; ++i)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        g.addEdge(src - 1, dest - 1, weight);
    }
    cout << g.longestPath(s - 1, t - 1);
    return 0;
}
