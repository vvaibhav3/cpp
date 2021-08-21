#include<bits/stdc++.h>
using namespace std;

int processArray(vector<int> v){

int i=0,ans=0,times=0;

while(i<v.size()){
    int x=0;
    while(v[i]<10){
        i++;
        x++;
    }
    if(x>0){
        times+=1;
        ans+=x;
    }
    i++;
}

return ans/times;
} 

int main(int argc, char const *argv[])
{
    vector<int> v;
    int n=0;
    while(1){
        cin>>n;
        if(n>=0)
            v.push_back(n);
        else
            break;
    }
    if(v.size()==0)
        return 0;
    cout<<processArray(v)<<endl;
    return 0;
}