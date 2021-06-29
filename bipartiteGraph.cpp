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

    //function to check if odd cycle then true so garph bipartite is not possible
    //using graph coloring method
    bool isOddCyle(T,vector<T>&);

    //biparatite algo
    bool isBipartite(vector<T>&);

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
bool graph<T>::isOddCyle(T node,vector<T> &color){
    queue<T> q;
    q.push(node);
    color[node]=1;
    while(!q.empty()){
        T nextNode=q.front();
        q.pop();

        for(auto nodes:adjList[nextNode]){
            if(color[nodes.first]==-1){
                color[nodes.first]=1-color[nextNode];
                q.push(nodes.first);
            }
            else if(color[nodes.first]==color[nextNode]){
                return true;
            }
        }
    }

    return false;
}

template<typename T>
bool graph<T>::isBipartite(vector<T> &color){

    //we can directly pass startnode but if graph is of multiple components
    //then it will not work so
    //we have to check all nodes are colored in case of multiple components
    //if any node is not colored then check again odd cycle
    for(auto nodes:adjList){
        if(color[nodes.first]==-1){
            //if true then odd cycle found
            if(isOddCyle(nodes.first,color)){
                return false;//so bipratite not possible
            }
        }
    }

    return true;
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

    //for storing indegree of nodes
    vector<int> color(v,-1);
    
    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest >> wt;
        g.addEdge(src, dest, wt, true);
    }

    cout<<"Adj List : \n";
    g.showAdjList();
    cout<<endl;

    if(!g.isBipartite(color)){
        cout<<"False : not possible..\n";
    }
    else{
        cout<<"True : possible..\n";
    }

    return 0;

}