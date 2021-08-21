#include<bits/stdc++.h>
using namespace std;

//Binary tree node takes o(N) in all cases for all operations

//node structure 
template <typename T>
class Node{
    public:
    //key of node
    T key;
    //left child pointer
    Node *left;
    //right child pointer
    Node *right;

    //constructor intializing both child pointer to NULL
    Node(){
        left=NULL;
        right=NULL;
        cout<<"\nnode created ....\n";
    }
};

//function to create new node 
template <typename T>
Node<T> * getNode(T data){
    Node<T> *temp=new Node<T>();
    temp->key=data;
    return temp;
}

//function to get inorder traversal of BT
template <typename T>
void inorder(Node<T> *temp){

    if(!temp)
        return;

    inorder(temp->left);
    cout<<temp->key<<" ";
    inorder(temp->right);
}

//handler to insert a particuler node at position
template <typename T>
void insert_handler(Node<T> *temp,string &path,int val,int pidx){
    if(path[pidx]=='L')
        if(temp->left)
            insert_handler(temp->left,path,val,pidx+1);
        else{
            temp->left=getNode(val);
            return;
        }
    else if(path[pidx]=='R')
        if(temp->right)
            insert_handler(temp->right,path,val,pidx+1);
        else{
            temp->right=getNode(val);
            return;
        }
}

//function to insert nodes of BT recursively
template <typename T>
void insert_rec(Node<T> *head,vector<string> &path,vector<int> &val){
    for(int i=0;i<path.size();i++){
        insert_handler(head,path[i],val[i],0);
    }
}

//function to insert nodes of BT non recursively
template <typename T>
void insert_non_rec(Node<T> *head,vector<string> &path,vector<int> &nodes){
    
    //temprary node to hold root addr
    Node<int> *start=NULL;
    for(int i=0;i<path.size();i++){
        int j=0;//index for path string
        start=head; //for each node get root node addr

        //traverse whole path string to insert node at apropriate position
        while(j<path[i].size() and start){
            if(path[i][j]=='L'){
                if(start->left)
                    start=start->left;
                else{
                    start->left=getNode(nodes[i]);
                    break;
                }
            }
            else{
                if(start->right)
                    start=start->right;
                else{
                    start->right=getNode(nodes[i]);
                    break;
                }
            }
            j++;
        }
    }
}

int main(int argc, char const *argv[])
{
    int N,R;
    cout << "Input : \n";
    cout << "1st line contains 2 values N - no of nodes and R root\n";
    cout << "2nd line N-1 child key with position - type : L (left) and R (right)\n";

    cin>>N>>R;

    vector<int> nodes(N);
    vector<string> path(N);

    for(int i=0;i<(N-1);i++){
        cin>>nodes[i]>>path[i];
    }

    Node<int> *head=getNode(R);
    insert_rec(head,path,nodes);
    inorder(head);
    return 0;
}
