#include<iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;

typedef pair<unsigned long long, unsigned long long> iPair;

class Graph
{
    unsigned long long V;
    list< pair<unsigned long long, unsigned long long> > *nodes;

public:
    Graph(unsigned long long V);
    void addEdge(unsigned long long u, unsigned long long v, unsigned long long w);
    void shortestPath(unsigned long long s);
};

Graph::Graph(unsigned long long V)
{
    this->V = V;
    nodes = new list<iPair> [V];
}

void Graph::addEdge(unsigned long long u, unsigned long long v, unsigned long long w)
{
    nodes[u].push_back(make_pair(v, w));
    nodes[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(unsigned long long src)
{
    priority_queue< iPair, vector <iPair>, greater<iPair> > pq;
    vector<unsigned long long> dist(V, ULLONG_MAX);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        unsigned long long u = pq.top().second;
        pq.pop();
        list< pair<unsigned long long, unsigned long long> >::iterator i;
        for (i = nodes[u].begin(); i != nodes[u].end(); ++i)
        {
            unsigned long long v = (*i).first;
            unsigned long long weight = (*i).second;
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    for (unsigned long long i = 0; i < V; ++i)

        if(i != src)
        {
            if(dist[i] == ULLONG_MAX)
                cout << -1 << " ";
            else
                cout << dist[i] << " ";
        }
        cout << "\n";
}

int main()
{
    unsigned long long times;
    cin >> times;
    for(unsigned long long j = 0; j < times;++j)
    {
        unsigned long long n,m;
        cin >> n >> m;
        Graph g(n);
        for(unsigned long long i = 0; i < m; ++i)
        {
            unsigned long long src, dest, weight;
            cin >> src >> dest >> weight;
            g.addEdge(src - 1, dest - 1, weight);
        }
        unsigned long long s;
        cin >> s;
        g.shortestPath(s - 1);
    }
    return 0;
}
