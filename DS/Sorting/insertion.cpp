#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Sort{

    vector<T> data;
    int size;  
    public:
        Sort(int);
        ~Sort();

        //getters
        void getItems();
        
        //setters
        void showData();

        //sorting algo - insertion
        void insertionAlgo();
};

template<typename T>
Sort<T>::Sort(int size){
    this->size=size;
    data.resize(size);
}

template<typename T>
Sort<T>::~Sort(){
    //delete data;
}

template<typename T>
void Sort<T>::getItems(){
    cout<<"Enter elements of list : \n";
    for(int i=0;i<size;i++){
        cin>>data[i];
    }
}

template<typename T>
void Sort<T>::showData(){
    cout<<"List : \n";
    for(int i=0;i<size;i++){
        cout<<data[i]<<"\t";
    }
    cout<<endl;
}

template<typename T>
void Sort<T>::insertionAlgo(){

    //k contains element from unsorted list to place in sorted list
    T k;

    int i=0,j=0;
    
    //for n-1 elements in list
    //except 1st element - data[0]
    for(i=1;i<size;i++){

        //element to place 
        k=data[i]; 

        for(j=i-1;j>=0 && data[j]>k;j--){
            data[j+1]=data[j];
        }
        data[j+1]=k;
        //printing data after each pass
        cout<<"after pass - "<<i<<" ";
        showData();
    }

    //printing list
    cout<<"Sorted ";
    showData();

}
int main(){

    int n;
    cout<<"Enter list size : ";
    cin>>n;

    Sort<int> s(n);

    //getting input 
    s.getItems();

    //showing list
    cout<<"Unsorted ";
    s.showData();

    //sorting list
    s.insertionAlgo();

    return 0;
}