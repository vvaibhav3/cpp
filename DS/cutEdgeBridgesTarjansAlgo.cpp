#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

template <typename T>
class graph
{
    int V;
    unordered_map<T, list<pair<T, int>>> adjList;
    vector<T> tpl_sorted_list;//using as stack
    queue<T> q;
public:
    graph(int);
    ~graph();

    //getters and setters
    void addEdge(T, T, int, bool);
    void removeEdge(T, T, int, bool);
    void showAdjList();

    //depth first search
    void dfs(T,int&,vector<T>&,vector<T>&,vector<T>&,unordered_map<T,T>&);

    //tarjan's algo - O(v+e) for finding bridges
    //bridge - removing edge increases no of components
    void tarjansAlgo();
};

template <typename T>
graph<T>::graph(int v)
{
    this->V = v;
}

template <typename T>
graph<T>::~graph()
{
    //delete[] adjList;
}

template <typename T>
void graph<T>::addEdge(T u, T v, int wt, bool bidir)
{

    adjList[u].push_back({v, wt});

    //if undirected graph
    if (bidir)
    {
        adjList[v].push_back({u, wt});
    }
}

template <typename T>
void graph<T>::removeEdge(T u, T v, int wt, bool bidir)
{

    //remove works on values where as erase works on position
    adjList[u].remove({v, wt});
    //if undirected graph
    if (bidir)
    {
        adjList[v].remove({u, wt});
    }
}

template <typename T>
void graph<T>::showAdjList()
{

    for (auto node : adjList)
    {
        cout << node.first << " : ";

        for (auto list_item : node.second)
            cout << list_item.first << " | " << list_item.second << " --> \t";

        cout << "\n";
    }
}

template<typename T>
void graph<T>::dfs(T node,int &time,vector<T> &parent,vector<T> &disc,vector<T> &low,unordered_map<T,T> &bridges){

    disc[node]=time;
    low[node]=time;
    time++;

    //to check if subgraph has back edge
    bool flag=true;

    for(auto nodes:adjList[node]){
        //if node is not visited then perform dfs and update low
        if(disc[nodes.first]==-1){
            parent[nodes.first]=node;
            dfs(nodes.first,time,parent,disc,low,bridges);
            low[node]=min(low[nodes.first],low[node]);
        }
        else if(parent[node]!=nodes.first){
            //if node is not parent and already visited then there is back edge
            low[node]=min(low[node],disc[nodes.first]);
            //flag false since back edge
            flag=false;
        }

        //if node u subgraph has no back edge then check disc<low if true then bride found 
        if(disc[node]<low[nodes.first] & flag){
            bridges.insert({node,nodes.first});
        }
    }
}

template<typename T>
void graph<T>::tarjansAlgo(){
  
  vector<T> parent(V,-1);
  vector<T> disc(V,-1);
  vector<T> low(V,-1);

  //to store edges
  unordered_map<T,T> bridges;
  int time=0;

  for(auto nodes:adjList){
      if(disc[nodes.first]==-1)
        dfs(nodes.first,time,parent,disc,low,bridges);
  }


//printing all bridges
cout<<"Bridges are : \n";
  for(auto edge:bridges){
      cout<<edge.first<<" -- "<<edge.second<<endl;
  }

  if(bridges.size()==0){
      cout<<"No bridges...\n";
  }
}

int main()
{
    int v, e; //no of vertex and edges
    cout << "Input : \n";
    cout << "1st line contains 2 values V - no of vertex and E - no of edges \n";
    cout << "2nd line choice of graph\n";
    cout << "3rd line contains 3 values ( U V WT ) for e edges \n";

    cin >> v >> e;

    //creating graph with v vertices
    graph<int> g(v);
    int src, dest, wt;

    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest >> wt;
        g.addEdge(src, dest, wt, true);
    }

    cout<<"Adj List : \n";
    g.showAdjList();
    cout<<endl;

    g.tarjansAlgo();

    return 0;
}