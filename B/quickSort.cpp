#include <iostream>
using namespace std;
void print_data(int[],int);
void quick_sort(int[],int,int);

void quick_sort(int data[],int l,int h){

	int start,end,pvt,temp;
	start=l;
	end=h;
	pvt=start;
	while(start<end){

		while(data[start]<=data[pvt]){
			start++;
		}

		while(data[end]>data[pvt]){
			end--;
		}

		if(start<end){
			temp=data[start];
			data[start]=data[end];
			data[end]=temp;
		}
		print_data(data,h);
	}

	if(l<h){

	temp=data[end];
	data[end]=data[pvt];
	data[pvt]=temp;
	//cout<<"\nend : "<<end<<" : "<<data[end]<<"\n";
	quick_sort(data,l,end-1);
	quick_sort(data,end+1,h);

	}
}

void print_data(int data[],int n){

	for(int i=0;i<n;i++){
		cout<<data[i]<<"\t";
	}
	cout<<"\n";
}

int main(){

int n;
cout<<"Enter size of list : ";
cin>>n;

int list[n];

cout<<"Enter items : \n";

for(int i=0;i<n;i++)
	cin>>list[i];

quick_sort(list,0,n-1);
print_data(list,n);

return 0;
}
