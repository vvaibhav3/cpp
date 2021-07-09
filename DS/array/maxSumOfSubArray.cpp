
//Sliding window technique 
#include<iostream>
#include<vector>
using namespace std;

//function to find max sum of subarray with given k - size of subarray
int maxSumSubarr(vector<int> &arr,int k){

    //maxSum will contain maximum sum among all subarray
    //sum contains sum for all subarray of k size
    int maxSum=0,sum=0;

    //two pointers start and end 
    int start=0,end=0;

    while(end<arr.size()){

        //add value to sum till end!=k
        sum=sum+arr[end];

        //if subarray size encountered then
        if((end-start+1)==k){
            //check max sum
            maxSum=max(sum,maxSum);
            //exclude arr[start] to move sliding window
            sum=sum-arr[start];
            start++;
        }
        end++;
    }

    return maxSum;
}

int main(int argc, char const *argv[])
{
    cout<<"Input : \n";
    cout<<"First line will contain 2 integer N - size of array and K - size of subarray \n";
    cout<<"Second line will contain N elements of array";

    int N,K;
    cin>>N>>K;
    vector<int> arr(N);

    for(int i=0;i<N;i++)
        cin>>arr[i];

    cout<<maxSumSubarr(arr,K);
    
    return 0;
}
