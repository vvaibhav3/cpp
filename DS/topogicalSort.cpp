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

    //directed graph cycle detecter
    bool directedCyle();
    int recCheckCycle(T,vector<T>);

    //depth first search
    void dfs(T,vector<T>&);

    //topological sort for directed acyclic graph (DAG)
    //using dfs+stack
    void topologicalSort();

    //kahans algo
    //using bfs
    void kahansAlgo(vector<T>);
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
bool graph<T>::directedCyle()
{
    vector<T> visited(V);

    //process all nodes in list one by one
    for (auto nodes : adjList)
    {
        //if recCheckCycle true then cycle found 
        if (recCheckCycle(nodes.first, visited))
        {
            cout << "Cycle detected....\n";
            return true;
        }
    }

    cout << "No cycle found...\n";
    return false;
}

template <typename T>
void graph<T>::dfs(T node,vector<T> &visited){
    
    if(find(visited.begin(),visited.end(),node)!=visited.end())
        return;

    visited.push_back(node);
    
    for(auto nodes:adjList[node]){
        if(find(visited.begin(),visited.end(),nodes.first)==visited.end())
            dfs(nodes.first,visited);
    }
    
    tpl_sorted_list.push_back(node);
    return;
}

template<typename T>
void graph<T>::topologicalSort(){

    vector<T> visited;
    //starting from vertex with indegree 0
    for(auto nodes:adjList){
        dfs(nodes.first,visited);
    }

    //printing the topological sort
    cout<<"Topological sort : \n";
    auto itr=tpl_sorted_list.end();
    while(itr!=tpl_sorted_list.begin()){
        itr--;
        cout<<*itr<<"\t";
    }
    cout<<endl;
    tpl_sorted_list.clear();
}

template<typename T>
void graph<T>::kahansAlgo(vector<T> indegree){

    for(int i=0;i<indegree.size();i++)
        if(indegree[i]==0)
            q.push(i);

    int count=0;
    vector<T> path;
   
    while(!q.empty()){
        T nextNode=q.front();
        q.pop();
        path.push_back(nextNode);

        for(auto nodes:adjList[nextNode]){
            indegree[nodes.first]-=1;
            if(indegree[nodes.first]==0)
                q.push(nodes.first);
            
        }
        count+=1;
    }

    if(count!=V){
        cout<<"Graph is cyclic...\n";
        return;
    }

    //printing the topological sort
    cout<<"Topological sort : \n";
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<"\t";
    }
    cout<<endl;
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
    vector<int> indegree(v,0);
    
    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest >> wt;
        g.addEdge(src, dest, wt, false);

        //incr indegree of node
        indegree[dest]++;
    }

    cout<<"Adj List : \n";
    g.showAdjList();
    cout<<endl;

    int ch;
    cout<<"Select algo : \n";
    cout<<"1.Topological sort (DFS)\n";
    cout<<"2.Topological sort (BFS - KAHAN'S Algo)\n";
    cin>>ch;

    switch(ch){

        case 1:
                //check if cycle contains
                if(g.directedCyle()){
                    cout<<"cyclic graph not possible...\n";
                    return 1;
                }
                //if graph is directed acyclic graph
                g.topologicalSort();
                break;
                
        case 2:
                //no need check sepratly for cycle
                g.kahansAlgo(indegree);
                break;

        default:
                cout<<"Wrong Choice...\n";
                return 1;
    }
    

    return 0;
}