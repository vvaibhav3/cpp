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
    void dfs(T,int&,vector<T>&,vector<T>&,vector<T>&,vector<T>&);

    //tarjan's algo - O(v+e) for finding articulation point
    //articulation point - removing vertex increases no of components in graph 
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
void graph<T>::dfs(T node,int &time,vector<T> &parent,vector<T> &disc,vector<T> &low,vector<T> &artPts){
    
    disc[node]=time;
    low[node]=time;
    time+=1;

    //children counter to count no of child of nodes
    int child=0;
    
    //to check if subgraph has back edge
    int flag=1;

    //cout<<node<<endl;
    for(auto nodes:adjList[node]){
        //if node is not visited then
        if(disc[nodes.first]==-1){
            //updating parent of node
            parent[nodes.first]=node;
            // perform dfs 
            dfs(nodes.first,time,parent,disc,low,artPts);
            //update low and child count
            low[node]=min(low[nodes.first],low[node]);
            child+=1;
        }
        else if(parent[node]!=nodes.first){
            //if node is not parent and already visited then there is back edge
            low[node]=min(low[node],disc[nodes.first]);
            //flag false since back edge
            flag=0;
        }

        //if node u subgraph has no back edge then check disc<low if true then bride found 
        if(disc[node]<low[nodes.first] && flag!=0){
            flag+=1;
            //cout<<node<<"\t"<<flag<<endl;
        }
    }

    // cout<<"low : \n";
    // for(auto l:low){
    //     cout<<l<<"\t";
    // }
    // cout<<endl;
    //Case -1 if node is root and child > 1 then node is articulation point
    //Case -2 if node is not root and disc[node]<low[child-nodes] then node is articulation point
    if(parent[node]==-1 and child>1){
        artPts.push_back(node);
    }
    else if(flag>=2){
        artPts.push_back(node);
    }

    flag=0;
}

template<typename T>
void graph<T>::tarjansAlgo(){
    vector<T> parent(V,-1);
    vector<T> disc(V,-1);
    vector<T> low(V,-1);
    vector<T> artPts;
    int time=0;

    //startnode is 0 since we are working root node so it is required
    dfs(0,time,parent,disc,low,artPts);

    //printing all AP
    cout<<"Articulation points are : \n";
    for(auto ap:artPts){
        cout<<ap<<"\t";
    }
    cout<<endl;
    
    if(artPts.size()==0){
        cout<<"No articulation point...\n";
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