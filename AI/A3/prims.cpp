#include <bits/stdc++.h>
using namespace std;

int main()
{
  int N, m;
  cin >> N >> m;
  vector<pair<int, int>> adj[N];

  int a, b, wt;
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> wt;
    adj[a].push_back(make_pair(b, wt));
    adj[b].push_back(make_pair(a, wt));
  }

  int parent[N], key[N], mst[N];

  for (int i = 0; i < N; i++)
  {
    key[i] = INT_MAX, mst[i] = false, parent[i] = -1;
  }

  key[0] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({0, 0});

  while (!pq.empty())
  {
    int node = pq.top().second;
    pq.pop();

    mst[node] = true;

    for (auto &i : adj[node])
    {
      int adjNode = i.first;
      int adjWt = i.second;
      if (mst[adjNode] == false && key[adjNode] > adjWt)
      {
        key[adjNode] = adjWt;
        parent[adjNode] = node;
        pq.push({adjWt, adjNode});
      }
    }
  }

  for (int i = 0; i < N; i++)
  {
    cout << i << " -> " << parent[i] << "\n";
  }

  return 0;
}
