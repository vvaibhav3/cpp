#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

template <typename T>
class graph
{
    int V;
    unordered_map<T, list<pair<T, int>>> adjList;

public:
    graph(int);
    ~graph();

    //getters and setters
    void addEdge(T, T, int, bool);
    void removeEdge(T, T, int, bool);
    void showAdjList();

    //directed graph cycle detecter
    void directedCyle();
    int recCheckCycle(T, vector<T>);

    //undirected graph cycle detecter
    int recCheckCycleUndirected(T, unordered_map<T,int>);
    void undirectedCyle();
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

template <typename T>
int graph<T>::recCheckCycle(T node, vector<T> visited)
{
    visited.push_back(node);
    for (auto nodes : adjList[node])
    {
        //check if already node is in visited list then cycle
        if (find(visited.begin(), visited.end(), nodes.first) != visited.end())
        {
            return 1;
        }

        if (recCheckCycle(nodes.first, visited))
            return 1;
    }
    return 0;
}

template <typename T>
void graph<T>::directedCyle()
{
    vector<T> visited(V);

    //process all nodes in list one by one
    for (auto nodes : adjList)
    {
        //if recCheckCycle true then cycle found 
        if (recCheckCycle(nodes.first, visited))
        {
            cout << "Cycle detected....\n";
            return;
        }
    }

    cout << "No cycle found...\n";
}


template<typename T>
int graph<T>::recCheckCycleUndirected(T node,unordered_map<T,int> visited){

    visited[node]+=1;
    for(auto nodes:adjList[node]){

        //if node is not visited
        if(visited[nodes.first]==0){
            if(recCheckCycleUndirected(nodes.first,visited))
                return 1;
            visited[nodes.first]+=1;
        }
        //if node is visited but not processed
        else if(visited[nodes.first]==1){
            visited[nodes.first]+=1;
        }
        //if node is visited and processed
        else if(visited[nodes.first]==2){
            return 1;
        }
    }
    return 0;
}

template<typename T>
void graph<T>::undirectedCyle(){

    //graph colouring method
    //visited list contains three values as below
    //0 = not visited
    //1 = visited but not processed
    //2 = visited and processed
    unordered_map<T,int> visited;

    //intializing all values to 0
    for(auto nodes:adjList){
        visited[nodes.first]=0;
    }

    for(auto nodes:adjList){
        if(recCheckCycleUndirected(nodes.first,visited)){
            cout << "Cycle detected....\n";
            return;
        }
    }
    
    cout << "No cycle found...\n";
}
int main()
{

    int ch;
    int v, e; //no of vertex and edges
    cout << "Input : \n";
    cout << "1st line contains 2 values V - no of vertex and E - no of edges \n";
    cout << "2nd line choice of graph\n";
    cout << "3rd line contains 3 values ( U V WT ) for e edges \n";

    cin >> v >> e;

    //creating graph with v vertices
    graph<int> g(v);
    int src, dest, wt;

    cout << "Choose graph type : \n 1. Directed graph \n 2.Undirected graph\n";
    cin >> ch;

    switch (ch)
    {
    case 1:
        for (int i = 0; i < e; i++)
        {
            cin >> src >> dest >> wt;
            g.addEdge(src, dest, wt, false);
        }
        cout<<"Adj List : \n";
        g.showAdjList();
        cout<<endl;
        g.directedCyle();
        break;

    case 2:
        for (int i = 0; i < e; i++)
        {
            cin >> src >> dest >> wt;
            g.addEdge(src, dest, wt, true);
        }
        cout<<"Adj List : \n";
        g.showAdjList();
        cout<<endl;
        g.undirectedCyle();
        break;

    default:
        cout << "Wrong choice" << ch << endl;
        return 1;
    }

    return 0;
}