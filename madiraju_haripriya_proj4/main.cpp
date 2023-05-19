#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <cstdlib>
#include <algorithm>// used for modifying elements like arrays,vectors
#include <limits.h> //determines the set of variable datatypes
using namespace std;

struct GraphEdge
{
  int u, v, weight;
};

vector<GraphEdge> edges;

int find3(int u, vector<int> &parent) /* using find3() function in implementation*/
{
  if (parent[u] == u)
  {
    return u;
  }
  return parent[u] = find3(parent[u], parent);
}

void union3(int u, int v, vector<int> &parent, vector<int> &rank) /* using union3() in implementation */
{
  u = find3(u, parent);
  v = find3(v, parent);

  if (rank[u] > rank[v])
  {
    parent[v] = u;
  }
  else if (rank[u] < rank[v])
  {
    parent[u] = v;
  }
  else
  {
    parent[v] = u;
    rank[u]++;
  }
}

bool compareGraphEdges(const GraphEdge &e1, const GraphEdge &e2)
{
  return e1.weight < e2.weight;
}

void generateGraph(int &n, vector<vector<int> > &AdjancyList)
{
  // Generate random number of vertices between 5 and 10
  n = rand() % 6 + 5;
  cout << "randomly selected " << n << " vertices" << endl;

  // Resize adjacency matrix
  AdjancyList.resize(n, vector<int>(n));

  // Randomly assign weights to edges
  for (int i = 0; i < n; i++) //using for loop to assign weights to the edges
  {
    for (int j = i + 1; j < n; j++) 
    {
      int weight = rand() % 10 + 1;
      AdjancyList[i][j] = weight;

      AdjancyList[j][i] = weight;

      GraphEdge edges1;
      edges1.u = i;
      edges1.v = j;
      edges1.weight = weight;

      edges.push_back(edges1);
    }
  }
}

void displayMatrix(const vector<vector<int> > &AdjancyList)
{
  for (int i = 0; i < AdjancyList.size(); i++)
  {
    for (int j = 0; j < AdjancyList[0].size(); j++)
    {
      cout << AdjancyList[i][j] << " ";
    }
    cout << endl;
  }
}

void primMST(const vector<vector<int> > &AdjancyList)
{
  int n = AdjancyList.size();
  vector<int> key(n, INT_MAX);
  vector<int> parent(n, -1);
  vector<bool> visited(n, false); //if visited 

  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push(make_pair(0, 0));
  key[0] = 0;

  while (!pq.empty())// if priority queue empty
  {
    int u = pq.top().second;
    pq.pop();
    visited[u] = true;

    for (int v = 0; v < n; v++)
    {
      if (AdjancyList[u][v] && !visited[v] && AdjancyList[u][v] < key[v])
      {
        key[v] = AdjancyList[u][v];
        parent[v] = u;
        pq.push(make_pair(key[v], v));// pushing a pairvalue into priority queue
      }
    }
  }

  // Print minimum spanning tree edges
  cout << "Prim's MST:" << endl;
  for (int i = 1; i < n; i++)
  {
    cout << "V" << parent[i] << "-V" << i << ": " << AdjancyList[i][parent[i]] << endl;
  }
}

void kruskalMST(const vector<GraphEdge> &edges, int n)
{
  vector<int> parent(n);
  vector<int> rank(n, 0);
  vector<GraphEdge> mst;

  // Initialize parent vector with each vertex as its own parent
  for (int i = 0; i < n; i++)
  {
    parent[i] = i;
  }

  // Sort edges in non-decreasing order of weight
  vector<GraphEdge> sortedEdges = edges;
  sort(sortedEdges.begin(), sortedEdges.end(), compareGraphEdges);

  // Add edges to MST if they don't create a cycle
  for (const GraphEdge &e : sortedEdges)
  {
    if (find3(e.u, parent) != find3(e.v, parent))
    {
      mst.push_back(e);
      union3(e.u, e.v, parent, rank);
    }
  }

  // Print minimum spanning tree edges
  cout << "Kruskal's MST:" << endl;
  for (const GraphEdge &e : mst)
  {
    cout << "V" << e.u << "-V" << e.v << ": " << e.weight << endl;
  }
}

int main()
{
  srand(time(NULL)); // Seed random number generator

  int n;
  vector<vector<int> > AdjancyList;

  generateGraph(n, AdjancyList);
  cout << "random matrix: " << endl;
  displayMatrix(AdjancyList);

  cout << "Select the algorithm: "; //type the algorthm in the terminal either prim|kruskal
  string option;
  cin >> option;

  if (option == "prim") //for the generated matrix if we select prim then the prims matrix is displayed with vertices
  {
    cout << "prim's matrix: " << endl;
    displayMatrix(AdjancyList);
    primMST(AdjancyList);
  }
  else if (option == "kruskal")
  {
    cout << "kruskal's matrix: " << endl; //for the generated matrix if we select kruskal then the kruskal matrix is displayed with vertices
    displayMatrix(AdjancyList);
    kruskalMST(edges, n);
  }
  else
  {
    cout << "error."<<endl ; //printing message as error if we choose other that prims or kruskal algorithm
  }

  return 0;
}
