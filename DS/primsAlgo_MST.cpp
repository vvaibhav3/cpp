#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

template<typename T>
class graph
{
int V;
unordered_map<T,list<pair<T,int>>> adjList;
public:
	graph(int);
	~graph();

	//getters and setters
	void addEdge(T,T,int,bool);
	void removeEdge(T,T,int,bool);
	void showAdjList();	

	//minimum spanning tree algo
	void primsAlgo(T);
};

template<typename T>
graph<T>::graph(int v){
	this->V=v;
}

template<typename T>
graph<T>::~graph(){
	//delete[] adjList;
}

template<typename T>
void graph<T>::addEdge(T u,T v,int wt,bool bidir){
	
	adjList[u].push_back({v,wt});
	
	//if undirected graph
	if(bidir){
		adjList[v].push_back({u,wt});
	}
}

template<typename T>
void graph<T>::removeEdge(T u,T v,int wt,bool bidir){

	//remove works on values where as erase works on position
	adjList[u].remove({v,wt});
	//if undirected graph
	if(bidir){
		adjList[v].remove({u,wt});
	}
}

template<typename T>
void graph<T>::showAdjList(){

	for(auto node:adjList){
		
		cout<<node.first<<" : ";
		
		for(auto list_item:node.second)
			cout<<list_item.first<<" | "<<list_item.second<<" --> \t";

		cout<<"\n";
	}
}

template<typename T>
void graph<T>::primsAlgo(T startnode){

    //for calculating distance
    unordered_map<T,int> dist;

    //this parent array list which shows path of MST
    unordered_map<T,T> path;

    //to avoid revisiting and re calculating of nodes
    vector<T> visited(V);
    for(auto nodes:adjList){
        dist[nodes.first]=INT_MAX;
    }

    //distance of first node to zero
    dist[startnode]=0;

    //parent of start node is none
    path[startnode]="0";

    //set contains elements in sorted manner
	//pair of distance and node so list will be sorted according to distance
    set<pair<int,T>> sorted_dist;
    	
	//initially startnode is added
    sorted_dist.insert({0,startnode});

    while(!sorted_dist.empty()){

        //getting next node with shortest distance to traverse adjlist
        auto temp=*sorted_dist.begin();
        int nextNodeDist=temp.first;
        T nextNode=temp.second;
        sorted_dist.erase(temp);

        //entering node to visited list
        visited.push_back(nextNode);

        for(auto node:adjList[nextNode]){

            //check min(dist[i],WTij) && node is note in visited list
            //update if distance is min
            if(node.second<dist[node.first] && find(visited.begin(),visited.end(),node.first)==visited.end()){
                
                dist[node.first]=node.second;

                //if node distance is previously present then update
				//update - first remove from set then insert new value
                auto x=sorted_dist.find({dist[node.first],node.first});
                if(x!=sorted_dist.end()){
                    sorted_dist.erase(x);
                }
                sorted_dist.insert({node.second,node.first});
                dist[node.first]=node.second;


                //updating parent of node
                path[node.first]=nextNode;
            }
        }
    }

    //printing path
    cout<<"Path : "<<endl;
    for(auto node:path){
        cout<<node.first<<" # "<<node.second<<" --> ";
    }

}
int main(){

    
	int v,e; //no of vertex and edges
	cout<<"Input : \nfirst line contains 2 values V - no of vertex and E - no of edges\n";
	cout<<"second line contains 3 values ( U V WT ) for e edges \n";

	cin>>v>>e;

	//creating graph with v vertices
	graph<string> g(v);

	string src,dest;
	int wt;
	for(int i=0;i<e;i++){
		cin>>src>>dest>>wt;
		g.addEdge(src,dest,wt,true);
	}

    cout<<"Enter startnode : ";
	cin>>src;

    g.primsAlgo(src);

    return 0;
}