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
    void dfs(T,unordered_map<T, list<pair<T, int>>>,vector<T>&,vector<T>&);

    //kosaraju algo - O(3v+e)
    void kosarajuAlgo();

    //dfs + check head of scc for tarjans algo
    void dfs2(T,int,vector<T>&,vector<T>&,vector<T>&);

    //tarjan's algo - O(v+e)
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
void graph<T>::dfs(T node,unordered_map<T,list<pair<T,int>>> adjList,vector<T> &visited,vector<T> &stk){

    //if visited then go back
    if(find(visited.begin(),visited.end(),node)!=visited.end())
        return;

    //if not visited then add node to visited list and traverse adj list
    visited.push_back(node);

    for(auto nodes:adjList[node]){
        if(find(visited.begin(),visited.end(),nodes.first)==visited.end()){
            dfs(nodes.first,adjList,visited,stk);
        }
    }

    //print node and add to stack
    cout<<node<<"\t";
    stk.push_back(node);
    return;
}

template<typename T>
void graph<T>::kosarajuAlgo(){

    vector<T> visited(V);
    vector<T> stk;//using vector as stack
    
    //step 1 - perform dfs and add nodes to stack while returning
    // T src;
    // cout<<"Enter startnode : ";
    // cin>>src;
    // dfs(src,adjList,visited,stk);

    for(auto nodes:adjList){
        if(find(visited.begin(),visited.end(),nodes.first)==visited.end())
            dfs(nodes.first,adjList,visited,stk);
    }

    //step 2 - create transpose of graph (reverse the edges)
    unordered_map<T,list<pair<T,int>>> transpose;

    for(auto nodes:adjList){
        for(auto n:nodes.second){
            transpose[n.first].push_back({nodes.first,n.second});
        }
    }

    //printing transpose of matrix
    cout<<"\nTranspose :: \n";
    for (auto node : transpose)
    {
        cout << node.first << " : ";

        for (auto list_item : node.second)
            cout << list_item.first << " | " << list_item.second << " --> \t";

        cout << "\n";
    }

    //step 3 - pop stack elements and perform dfs on every element
    //each dfs gives on strongly connected component
    
    //using vector to check visited nodes again for transpose graph
    visited.clear();
    vector<T> stk2;

    while(stk.size()>0){
        //pop node from stack
        T node=*(stk.end()-1);
        stk.pop_back();

        //check if node is already processed
        if(find(visited.begin(),visited.end(),node)==visited.end()){
            cout<<"Stongly connected component :: \n";
            dfs(node,transpose,visited,stk2);
            cout<<endl;
        }
    }

}

template<typename T>
void graph<T>::dfs2(T node,int time,vector<T> &disc,vector<T> &low,vector<T> &stk){

    //if not visited then add node to visited list and traverse adj list
    disc[node]=time;
    low[node]=time;
    time+=1;

    cout<<"current node : "<<node<<endl;
    //add node to stack to know the back and cross edges
    stk.push_back(node);

    for(auto nodes:adjList[node]){
        if(disc[nodes.first]==-1){
            dfs2(nodes.first,time,disc,low,stk);
            low[node]=min(low[nodes.first],low[node]);
        }
        else if(find(stk.begin(),stk.end(),nodes.first)!=stk.end()){
            low[node]=min(low[node],disc[nodes.first]);
        }
    }

    if(disc[node]==low[node]){
        cout<<"Strongly connected component : \n";
        auto top=stk.end()-1;
        while(*top!=node){
            cout<<*top<<"\t";
            stk.pop_back();
            top=stk.end()-1;
        }
        cout<<*top<<"\t";
        stk.pop_back();
        cout<<endl;
    }
    return;
}

template<typename T>
void graph<T>::tarjansAlgo(){

    vector<T> stk;//using vector as stack
    vector<T> disc(V,-1);
    vector<T> low(V,-1);
    for(auto nodes:adjList)
        if(disc[nodes.first]==-1)
            dfs2(nodes.first,0,disc,low,stk);

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
        g.addEdge(src, dest, wt, false);
    }

    cout<<"Adj List : \n";
    g.showAdjList();
    cout<<endl;

    // g.kosarajuAlgo();
    g.tarjansAlgo();

    return 0;
}