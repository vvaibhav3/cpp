#include<bits/stdc++.h>
using namespace std;
#define lli long long int
int solve(lli n,lli d,vector<lli> items) {

    lli ans=0;
    lli i=0;
    sort(items.begin(),items.end());

    while(d>=items[i%n]){
        d=d-items[i%n];
        i++;
        ans++;
        // cout<<items[i]<<endl;
    }
    return ans;
}  

int main(int argc, char const *argv[])
{
    
    lli N,D;
    cin>>N>>D;
    vector<lli> items(N,0);
    for(lli i=0;i<N;i++)
    {
        lli x;
        cin>>x;
        items[i]=x;
    }

    cout<<solve(N,D,items)<<endl;

    return 0;
}
