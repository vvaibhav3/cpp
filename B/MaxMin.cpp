#include<iostream>
#include<vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int N;
    cout<<"\n\n\n\033[1;32m--------------MAX-MIN OF LIST----------------\033[0m\n\n";
    cout<<"Enter list size : ",cin>>N;
    
    vector<int> arr(N);

    cout<<"\nEnter elements : \n";
    for(int i=0;i<N;i++){
        cin>>arr[i];
    }

    int max=arr[0],min=arr[0];

    for(int i=1;i<N;i++){
        if(min>arr[i])
            min=arr[i];
        if(max<arr[i])
            max=arr[i];
    }

    cout<<"\n\033[1;32m------------------------------------------\033[0m\n\n";
    cout<<"\033[1;31mMax : "<<max<<" Min : "<<min<<"\033[0m\n";
    cout<<"\n\033[1;32m------------------------------------------\033[0m\n\n";
    return 0;
}
