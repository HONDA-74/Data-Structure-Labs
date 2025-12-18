#include <iostream>
#include<vector>
#include<list>
#include<stack> 
#include<functional>
#include<algorithm>
#include<queue>
using namespace std;

template<class VertexType>
class Graph
{
    int numVertices ;               // Number of vertices + the pointer of the index of the next vertex
    VertexType vertices[50] ;       // Array of vertices
    int edges[50][50] ;             // Adjacency matrix 
    bool marks[50];                 // Marks array

public:
    explicit Graph() {numVertices = 0;}

    void MakeEmpty()
    {
    numVertices = 0;
    for (int i = 0; i < 50; i++)
    {
        marks[i] = false;
        for (int j = 0; j < 50; j++)
            edges[i][j] = 0; 
    }
    }

    bool IsEmpty(){ return numVertices == 0; }

    bool IsFull(){ return numVertices >= 50; }

    void AddVertex (const VertexType& vertex)
    {
    if (!IsFull())
    {
        vertices[numVertices] = vertex;
        numVertices++;
    }
    }

    void AddEdge(VertexType fromVertex ,VertexType toVertex , int Weight )
    {
    int row = GetIndex(fromVertex);
    int col = GetIndex(toVertex);

    if (row != -1 && col != -1)
        edges[row][col] = Weight;

    }

    int GetPathWeight (VertexType fromVertex ,VertexType toVertex)
    {
    int row = GetIndex(fromVertex);
    int col = GetIndex(toVertex);
    return edges[row][col];
    }

    int GetIndex (const VertexType& vertex)
    {
    for (int i = 0; i < numVertices; i++)
        if (vertices[i] == vertex)
            return i;
    return -1;
    }

    void GetAdjVertices (VertexType vertex , queue<VertexType> & VertexQ)
    {
    int row = GetIndex(vertex);
    for (int i = 0; i < numVertices; i++)
        if (edges[row][i] != 0)
            VertexQ.push(vertices[i]);
    }

    void ClearMarks ()
    {
    for (int i = 0; i < numVertices; i++)
        marks[i] = false;
    }

    void MarkVertex(VertexType vertex)
    {
    int idx = GetIndex(vertex);
    if (idx != -1)
        marks[idx] = true;
    }

    bool IsMarked (VertexType vertex)
    {
    int idx = GetIndex(vertex);
    return (idx != -1) ? marks[idx] : false;
    }


    void DepthFirstSearch (const VertexType& startVertex , const VertexType& endVertex)
    {
    stack<int> S;
    ClearMarks();

    int startIdx = GetIndex(startVertex);
    S.push(startIdx);
    marks[startIdx] = true;

    while (!S.empty())
    {
        int current = S.top(); S.pop(); //b // c // d // e
        cout << vertices[current] << " "; // a // b // c // d

        if (vertices[current] == endVertex)
            return; // found end

        for (int i = numVertices-1; i >= 0; i--)
        {
        if (edges[current][i] != 0 && !marks[i])
        {
            S.push(i); // a , c , d  , e
        }
        }
        marks[current] = true; // a // b// c //d
    }
    }  

    void Dijkstra (const VertexType& startVertex)
    {
    const int INF = 1e9; 
    int startIdx = GetIndex(startVertex);

    vector<int> dist(numVertices, INF);   
    vector<int> prev(numVertices, -1);   
    vector<bool> visited(numVertices, false);

    dist[startIdx] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, startIdx});

    while(!pq.empty())
    {
        int u = pq.top().second; pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for(int v = 0; v < numVertices; v++)
        {
            if(edges[u][v] != 0)
            {
                int weight = edges[u][v];
                if(dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    cout << "Shortest distances from " << startVertex << ":\n";
    for(int i=0; i<numVertices; i++)
    {
        cout << vertices[i] << " : ";
        if(dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }

    cout << "\nPaths from " << startVertex << ":\n";
    for(int i=0; i<numVertices; i++)
    {
        if(i == startIdx) continue;
        if(dist[i] == INF) { cout << vertices[i] << " : No path\n"; continue; }

        vector<int> path;
        for(int at=i; at!=-1; at=prev[at]) path.push_back(at);

        cout << vertices[i] << " : ";
        for(int j=path.size()-1; j>=0; j--) cout << vertices[path[j]] << " ";
        cout << "\n";
    }
    }

};

int main(){
    Graph<string> g;


    g.AddVertex("A");
    g.AddVertex("B");
    g.AddVertex("C");
    g.AddVertex("D");
    g.AddVertex("E");

    g.AddEdge("A", "B", 2);
    g.AddEdge("A", "C", 5);
    g.AddEdge("B", "C", 1);
    g.AddEdge("B", "D", 3);
    g.AddEdge("C", "D", 2);
    g.AddEdge("D", "E", 1);

    cout << "Depth First Search from A to E:\n";
    g.DepthFirstSearch("A", "E");

    cout << "\n\nDijkstra's Algorithm starting from A:\n";
    g.Dijkstra("A");



    return 0;
}
