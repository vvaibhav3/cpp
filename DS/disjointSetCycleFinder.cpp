#include<bits/stdc++.h>
using namespace std;

//disjoint set = diset
vector<int> diset;

//function to return absolute parent of node
int find(int node){
    //base case
    //if no parent then return node
    if(diset[node]==-1)
        return node;

    //recursive work
    //pass parent of node to get again next parent
    return find(diset[node]); 
}

//union operation of disjoint set
void unionOp(int e1,int e2){

    //find absolute parent of element 1
    int ap1=find(e1);

    //find absolute parent of element 2
    int ap2=find(e2);
    
    //change parent of ap1 to ap2 i.e. ap1 points to ap2
    diset[ap1]=ap2;

}

bool isCycle(vector<pair<int,int>> edgeList){

    //get every edge from edge-list
    for(auto edge:edgeList){
        //find absolute parent of src node
        int ap1=find(edge.first);

        //find absolute parent of dest node
        int ap2=find(edge.second);

        //if absolute parents are same then cycle found return true
        if(ap1==ap2){
             return true;
        }
        
        //union operation
        //since we have already taken apsolute parents so no need to call union func again
        diset[ap1]=ap2;

    }

    return false;
}
int main(){

	int v,e; //no of vertex and edges
	cout<<"-----------------------Undirected graph cycle detection---------------------------------\n";
    cout<<"Input : \nfirst line contains 2 values V - no of vertex and E - no of edges\n";
	cout<<"second line contains 3 values ( U V) for e edges \n";
	cin>>v>>e;

    diset.resize(v,-1);

    //preparing edge list
    vector<pair<int,int>> edgeList;
    int src,dest;
    for(int i=0;i<e;i++){
        cin>>src>>dest;
        edgeList.push_back({src,dest});
    }

    if(isCycle(edgeList))
        cout<<"Cycle detected....\n";
    else
        cout<<"No Cycle....\n";


    return 0;
}