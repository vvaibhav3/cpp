#include<bits/stdc++.h>
using namespace std;

//all pair shortest path algo
void floydWarshallAlgo(vector<vector<int>> &adjMatrix){
	
	//copying adjMatrix;
	vector<vector<int>> dist(adjMatrix);

    //for V vertex
    for(int k=0;k<dist.size();k++)
        for(int i=0;i<dist.size();i++) //for every Kth vertex row
            for(int j=0;j<dist.size();j++){ //for every Kth vertex col
                
                //if any of the distance is infinity then keep distance as it is prev
                if(dist[i][k]==INT_MAX or dist[k][j]==INT_MAX)
                    continue;
                
                //now min(dist[i][j],dist[i][k]+dist[k][j])
                if(dist[i][k]+dist[k][j] < dist[i][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
    
    //negative weight cycle detection
    for(int i=0;i<dist.size();i++){
        if(dist[i][i]<0){
            cout<<"Negative weight cycle detected ........... ";
            return;
        }
    }

    //printing the distance
    cout<<"Shortest distance for all nodes : \n";
    for(int i=0;i<dist.size();i++){
        for(int j=0;j<dist.size();j++)
            cout<<dist[i][j]<<"\t";

        cout<<"\n";
    }
}           

int main(){
    
    int v,e; //no of vertex and edges
	cout<<"Input : \nfirst line contains 2 values V - no of vertex and E - no of edges\n";
	cout<<"second line contains 3 values ( U V WT ) for e edges \n";

	cin>>v>>e;

    //adjacency matrix V*V
	vector<vector<int>> adjMatrix(v,vector<int> (v,INT_MAX));
	int src,dest,wt;

	for(int i=0;i<e;i++){
		cin>>src>>dest>>wt;
		adjMatrix[src][dest]=wt;
	}

    //intialize diagonal value to zero
    for(int i=0;i<v;i++){
        adjMatrix[i][i]=0;
    }

	floydWarshallAlgo(adjMatrix);

    return 0;
}