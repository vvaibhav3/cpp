#include<bits/stdc++.h>
using namespace std;
#define lli long long int

void solve(vector<int> arr,int n,int k){
    unordered_map<lli,lli> data;
    sort(arr.begin(),arr.end());
    lli max_occur=arr[0];
    
    for(int i=0;i<n;i++){
        data[arr[i]]++;
    }
    
    int j,temp;
    for(int i=n-1;i>0;i--){
        j=i-1;
        temp=k;
        while(temp>0 && j>=0){
            if(arr[j]!=arr[i]){
                temp=temp-(arr[i]-arr[j]);
                if(temp>=0){          
                   // cout<<arr[i]<<endl;
                    data[arr[i]]++;
                }
            }
            j--;
        }
        
        if(data[max_occur]<data[arr[i]]){
            max_occur=arr[i];
        }
    }
    cout<<data[max_occur]<<max_occur<<endl;

}

int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    lli k,temp;
    cin>>k;
    vector<int> arr(n);

    for(int i=0;i<n;i++){
        cin>>temp;
        arr[i]=temp;
    }   

    solve(arr,n,k);

    return 0;
}
