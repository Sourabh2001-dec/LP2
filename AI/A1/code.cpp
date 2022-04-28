#include <bits/stdc++.h>
using namespace std;

struct Edge
{
  int src, dest;
};

class Graph
{
public:
  map<int, vector<int>> adjList;

  Graph(vector<Edge> const &edges)
  {
    for (auto &edge : edges)
    {
      adjList[edge.src].push_back(edge.dest);
      adjList[edge.dest].push_back(edge.src);
    }
  }
};

void recursiveDFS(Graph const &graph, int v, unordered_set<int> &discovered)
{
  discovered.insert(v);

  cout << v << " ";

  for (int u : graph.adjList.find(v)->second)
  {
    if (discovered.find(u) == discovered.end())
    {
      recursiveDFS(graph, u, discovered);
    }
  }
}

void recursiveBFS(Graph const &graph, queue<int> &q, unordered_set<int> &discovered)
{
  if (q.empty())
  {
    return;
  }

  int v = q.front();
  q.pop();
  cout << v << " ";

  for (int u : graph.adjList.find(v)->second)
  {
    if (discovered.find(u) == discovered.end())
    {
      discovered.insert(u);
      q.push(u);
    }
  }

  recursiveBFS(graph, q, discovered);
}

int main()
{
  int choice;
  Graph *graph = nullptr;
  while (choice != 4)
  {
    cout << "1. Enter graph" << endl;
    cout << "2. BFS" << endl;
    cout << "3. DFS" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;

    if (choice == 1)
    {
      int noOfEdges;
      vector<Edge> edges;
      cout << "Enter number of edges: ";
      cin >> noOfEdges;
      while (noOfEdges--)
      {
        int src, dest;
        cin >> src >> dest;
        edges.push_back({src, dest});
      }

      if (graph != nullptr)
      {
        delete graph;
      }
      graph = new Graph(edges);
    }
    else if (choice == 2)
    {
      cout << "Enter node to start BFS from : ";
      int node;
      cin >> node;
      unordered_set<int> discovered;

      queue<int> q;
      discovered.insert(node);

      q.push(node);

      recursiveBFS(*graph, q, discovered);
      cout << endl;
    }
    else if (choice == 3)
    {
      cout << "Enter node to start DFS from : ";
      int node;
      cin >> node;
      unordered_set<int> dfsDiscovered;

      recursiveDFS(*graph, node, dfsDiscovered);
      cout << endl;
    }
    else if (choice == 4)
    {
      cout << "Exiting" << endl;
    }
    else
    {
      cout << "Invalid choice" << endl;
    }
  }

  return 0;
}