#include<bits/stdc++.h>
using namespace std;

//node structure
struct node{
    int parent;
    int rank;
};

//disjoint set = diset
vector<node> diset;

//function to return absolute parent of node
int find(int v){
    //base case
    //if no parent then return node
    if(diset[v].parent==-1)
        return v;

    //recursive work
    //pass parent of node to get again next parent
    //update absolute parent of node for path compression
    return diset[v].parent=find(diset[v].parent); 
}

//union operation of disjoint set
void unionOp(int e1,int e2){

    //find absolute parent of element 1
    int ap1=find(e1);

    //find absolute parent of element 2
    int ap2=find(e2);
    
    //check ranks of both absolute parent whichever is min that points to another
    //if same rank parent of ap1 to ap2 i.e. ap1 points to ap2
    if(diset[ap1].rank<diset[ap2].rank)
        diset[ap1].parent=ap2;
    else if(diset[ap1].rank>diset[ap2].rank)
        diset[ap2].parent=ap1;
    else{
        diset[ap1].parent=ap2;
        diset[ap1].rank+=1;
    }
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
        unionOp(ap1,ap2);

    }

    return false;
}
int main(){

	int v,e; //no of vertex and edges
	cout<<"-----------------------Undirected graph cycle detection---------------------------------\n";
    cout<<"Input : \nfirst line contains 2 values V - no of vertex and E - no of edges\n";
	cout<<"second line contains 3 values ( U V) for e edges \n";
	cin>>v>>e;

    diset.resize(v);

    for(int i=0;i<v;i++)
        diset[i].parent=-1,diset[i].rank=0;

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