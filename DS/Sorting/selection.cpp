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

        //sorting algo
        void selectionAlgo();
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
void Sort<T>::selectionAlgo(){

    //for sorting position of min element in list
    int min=0;

    //n-1 passes
    for(int i=0;i<size-1;i++){
        //initial pos of mini i since first i-1 elements are placed already
        int min=i; 

        //j=i again becoz of first i-1 elements are placed already
        //getting pos of min element in list
        for(int j=i;j<size;j++){
            if(data[j]<data[min])
                min=j;
        }

        //check if pos of i & min are not same then swap min with i
        if(i!=min){
            //swapping without extra var this workes for only numbers not for string
            // data[i]+=data[min];
            // data[min]=data[i]-data[min];
            // data[i]-=data[min];

            T temp=data[min];
            data[min]=data[i];
            data[i]=temp;
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
    s.selectionAlgo();

    return 0;
}