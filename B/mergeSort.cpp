#include<iostream>
using namespace std;
int n;

void merge(int arr[],int l,int m,int r){
    	int t=0,arr2[n];
    	//cout<<"l : "<<l<<" r : "<<r<<endl;
	int i=0,j=m+1;

	while(i<=m && j<=r){
		if(arr[i]<arr[j]){
			arr2[t]=arr[i];
			i++;
			t++;
		}
		else{
			arr2[t]=arr[j];
			j++;
			t++;
		}

	}

	while(i<=m){
		arr2[t]=arr[i];
		i++;
		t++;
	}

	while(j<=r){
		arr2[t]=arr[j];
		j++;
		t++;
	}
    /*for(int i=l;i<=r;i++){
        if(arr[i]>arr[i+1]){
            //swaping
            temp=arr[i+1];
            arr[i+1]=arr[i];
            arr[i]=temp;
            cout<<"arr [i] : "<<arr[i]<<"\narr[i+1] : "<<arr[i+1]<<endl;
        }
    }*/

    //cout<<"merge : "<<endl;
    for(int v=0;v<t;v++)
        arr[v]=arr2[v];

    //cout<<"\n";
}

void devider(int arr[],int l,int r){
    int mid;
    // cout<<"l : "<<l<<" r : "<<r<<endl;
    if(l>=r){
        return;
    }
    else{
        mid=(l+r)/2;
        //cout<<"mid : "<<mid<<"\n";
        devider(arr,l,mid);
        // cout<<"second half : "<<endl;
        devider(arr,mid+1,r);
        // cout<<"second half : "<<endl;
        merge(arr,l,mid,r);
    }
}

int main(){
    cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>MERGE SORT<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";
    cout<<"Enter size of array : \n";
    cin>>n;
    int data[n];

    cout<<"Enter elements of array : \n";
    for(int i=0;i<n;i++)
        cin>>data[i];

    cout<<"Unsorted data : \n";
    for(int i=0;i<n;i++)
        cout<<data[i]<<"\t";

    cout<<"\n"; 
    devider(data,0,n-1);

    cout<<"sorted data : \n";
    for(int i=0;i<n;i++)
        cout<<data[i]<<"\t";

    cout<<"\n";
    return 0;
}
