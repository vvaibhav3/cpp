#include<bits/stdc++.h>
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

	//single ssrc shortest path algo
	void dijstraAlgo(T,T);
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
void graph<T>::dijstraAlgo(T startnode,T endnode){

	//distance array
	unordered_map<T,int> dist;

	//for storing nodes to print path
	vector<T> path;

	//intializing all nodes distance to infinity
	for(auto nodes:adjList){
		dist[nodes.first]=INT_MAX;
	}

	//distance of first node to zero
	dist[startnode]=0;

	//set contains elements in sorted manner
	//pair of distance and node so list will be sorted according to distance
	set<pair<int,T>> sorted_dist;
	
	//initially startnode is added
	sorted_dist.insert({0,startnode});

	while(!sorted_dist.empty()){

		//getting node to traverse adjlist
		auto temp=*sorted_dist.begin();
		T nextNode=temp.second;
		int nextNodeDist=temp.first;

		//entering node to path list
		path.push_back(nextNode);
		
			cout<<nextNode<<endl;
		//remove once the node is taken
		sorted_dist.erase(temp);

		for(auto node: adjList[nextNode]){

			//check d[nextNode][node] = min( currentDist+WT , d[nextNode][node])
			if(nextNodeDist+node.second < dist[node.first]){
				
				//if node distance is previously present then update
				//update - first remove from set then insert new value
				auto x=sorted_dist.find({dist[node.first],node.first});
				if(x!=sorted_dist.end()){
					sorted_dist.erase(x);
				}

				sorted_dist.insert({nextNodeDist+node.second,node.first});
				dist[node.first]=nextNodeDist+node.second;
			}
		}
	}

	//printing distance of all nodes
	for(auto node: dist){
		cout<<node.first<<" "<<node.second<<endl;
	}

	cout<<"Path : \n";
	for(auto node:path){
		if(node==endnode)
			break;
		cout<<node<<" --> ";
	}
	cout<<endnode<<"\n";
}

int main(int argc, char const *argv[])
{
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

	g.showAdjList();
	cout<<"Enter startnode : ";
	cin>>src;

	cout<<"Enter endnode : ";
	cin>>dest;
	g.dijstraAlgo(src,dest);


	
	return 0;
}