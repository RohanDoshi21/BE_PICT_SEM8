#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
private:
    int vertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }

    // BFS
    void BFS(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> queue;
        queue.push(start);
        visited[start] = true;

        while (!queue.empty())
        {
            int current;

#pragma omp parallel shared(queue, visited)
            {

#pragma omp single
                {
                    current = queue.front();
                    queue.pop();
                    cout << "Thread " << omp_get_thread_num() << " visited " << current << endl;
                }

#pragma omp for
                for (int i = 0; i < adjList[current].size(); i++)
                {
                    if (!visited[adjList[current][i]])
                    {
#pragma omp critical
                        {
                            queue.push(adjList[current][i]);
                            visited[adjList[current][i]] = true;
                        }
                    }
                }
            }
        }
    }

    void DFS(int start)
    {
        vector<bool> visited(vertices, false);
        DFSUtil(start, visited);
    }

    void DFSUtil(int v, vector<bool> &visited)
    {

#pragma omp critical
        {
            visited[v] = true;
            cout << "Thread " << omp_get_thread_num() << " visited " << v << endl;
        }

#pragma omp parallel for
        for (int i = 0; i < adjList[v].size(); i++)
        {
            int u = adjList[v][i];
            if (!visited[u])
            {
                DFSUtil(u, visited);
            }
        }
    }
};

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 1);
    g.addEdge(2, 4);

    // Graph g(10);
    // g.addEdge(0, 1);
    // g.addEdge(0, 2);
    // g.addEdge(0, 3);
    // g.addEdge(1, 2);
    // g.addEdge(1, 4);
    // g.addEdge(2, 3);
    // g.addEdge(2, 4);
    // g.addEdge(2, 5);
    // g.addEdge(3, 5);
    // g.addEdge(3, 6);
    // g.addEdge(4, 5);
    // g.addEdge(4, 7);
    // g.addEdge(5, 6);
    // g.addEdge(5, 7);
    // g.addEdge(5, 8);
    // g.addEdge(6, 8);
    // g.addEdge(7, 8);
    // g.addEdge(7, 9);
    // g.addEdge(8, 9);

    g.printGraph();

    cout << endl;
    cout << "BFS traversal starting from vertex 0: " << endl;
    g.BFS(0);
    cout << endl;


    cout << "DFS traversal starting from vertex 0: " << endl;
    g.DFS(0);
    cout << endl;

    return 0;
}