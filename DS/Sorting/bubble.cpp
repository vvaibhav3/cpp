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

        //sorting algo modified bubble sort 
        void bubbleAlgo();
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
void Sort<T>::bubbleAlgo(){

    //true if any pair is swapped otherwise false
    bool swap;

    //n-1 passes
    for(int i=0;i<size-1;i++){

        //set swap initialy false so if no swap we will stop
        swap=false;

        //since after each i pass last i+1 elements are already sorted
        for(int j=0;j<(size-i-1);j++){
            //check every adj elements to swap
            if(data[j+1]<data[j]){
                swap=true;
                T temp=data[j+1];
                data[j+1]=data[j];
                data[j]=temp;
            }
        }
        //printing data after each pass
        cout<<"after pass - "<<i<<" ";
        showData();

        //chcek if swapped
        if(!swap){
            cout<<"No of passes done :"<<i<<endl;
            break;
        }
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
    s.bubbleAlgo();

    return 0;
}