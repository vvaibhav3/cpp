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
    
    //to check if graph is connected i.e. performing dfs and cheking if all nodes are visited
    void dfs(T,vector<T>&);

    //Euler graph 
    void eulerGraph();
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

//normal dfs function to traverse graph
template<typename T>
void graph<T>::dfs(T node,vector<T> &visited){

    visited[node]=1;

    for(auto nodes:adjList[node]){
        if(!visited[nodes.first])
            dfs(nodes.first,visited);
    }

    return;

}

template<typename T>
void graph<T>::eulerGraph(){

    vector<T> visited(V,0);

    //step 1- check connectivity
    
    //tarverse graph
    for(auto nodes:adjList){
        if(!visited[nodes.first]){
            dfs(nodes.first,visited);
            break;
        }
    }

    //to count odd degree vertices
    int count=0;

    //check if all node visited
    for(auto nodes:adjList){
        //if node is not visited then check if degree - false then graph is not connected
        if(!visited[nodes.first]){
            //degree check
            if((nodes.second).size()!=0){
                cout<<"graph is not euler becoz it is not an connected graph....\n";
                return;
            }
        }
        else{
            //check odd degree vertices
            if((nodes.second).size()%2){
                //cout<<"odd deg : "<<nodes.first<<"\t"<<(nodes.second).size()<<endl;
                count+=1;
            }
        }
    }

    //if odd degree vertices are 1 or 2 then semi euler and greater than 2 then not euler
    if(count and count==2){
        cout<<"graph is semi euler graph...\n";
    }
    else if(count>2){
        cout<<"graph is not euler....\n";
    }
    else{
        //if count=0 then graph is euler
        cout<<"graph is euler graph...\n";
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

    g.eulerGraph();

    return 0;
}