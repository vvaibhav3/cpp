#include <iostream>
using namespace std;

#define MAX 99999999

class EdgeList{
    public:
    int u;
    int v;
    int wt;
    void getEdge(){
        cout<<u<<"  "<<wt<<"  "<<v<<"\n";
    }
};

void showEdgeList(EdgeList *edges,int e){

    cout<<"U  WT  V\n";
    for(int i=0;i<e;i++){
        edges[i].getEdge();
    }
}

int* bellmanFordRec(EdgeList *edges,int di[],int v,int e,int currV){

    if(currV<(v-1)){
        for(int i=0;i<e;i++){
            //cout<<"cost : "<<(di[edges[i].u]+edges[i].wt)<<"\n";
            if( (di[edges[i].u]+edges[i].wt) < di[edges[i].v]){
                di[edges[i].v]=(di[edges[i].u]+edges[i].wt);
            }
        }
        return di=bellmanFordRec(edges,di,v,e,currV+1);
    }
}

void bellmanFord(EdgeList *edges,int *di,int v,int e){


    for(int k=0;k<(v-1);k++){
        
        for(int i=0;i<e;i++){
            //cout<<"cost : "<<(di[edges[i].u]+edges[i].wt)<<"\n";
            if( (di[edges[i].u]+edges[i].wt) < di[edges[i].v]){
                di[edges[i].v]=(di[edges[i].u]+edges[i].wt);
            }
        }
        cout<<"\n";
    }

    for(int i=0;i<e;i++){
            //cout<<"cost : "<<(di[edges[i].u]+edges[i].wt)<<"\n";
            if( (di[edges[i].u]+edges[i].wt) < di[edges[i].v]){
                cerr<<"Negative weight cycle....\n";
                exit(1);
            }
    }

}

int main(int argc, char const *argv[])
{

    int v,e;
    cout<<"Enter no of vertex : ";
    cin>>v;

    cout<<"Enter no of edges : ";
    cin>>e;

    EdgeList *edges=new EdgeList[e];

    for(int i=0;i<e;i++){
        cout<<"U : ";
        cin>>edges[i].u;

        cout<<"V : ";
        cin>>edges[i].v;

        cout<<"WT : ";
        cin>>edges[i].wt;
    }

    cout<<"\n";
    showEdgeList(edges,e);


    int *di=new int[v];

    //intializing distance with max
    for(int i=0;i<v;i++){
        di[i]=MAX;
    }
    //src node distance = 0
    di[0]=0;

    cout<<"\n";
    bellmanFord(edges,di,v,e);
    cout<<"\nDistance : \n";
    for(int i=0;i<v;i++){
        cout<<i<<" : "<<di[i]<<"\n";
    }

    cout<<"\nRecursive : "<<"\n";
    //intializing distance with max
    for(int i=0;i<v;i++){
        di[i]=MAX;
    }
    //src node distance = 0
    di[0]=0;

    di=bellmanFordRec(edges,di,v,e,0);

    cout<<"\nDistance : \n";
    for(int i=0;i<v;i++){
        cout<<i<<" : "<<di[i]<<"\n";
    }

    delete[] di;
    delete[] edges;
    /* code */
    return 0;
}
