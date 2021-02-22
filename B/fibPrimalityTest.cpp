#include<iostream>
using namespace std;
#define lli long long int

lli m;

lli moduloAdd(lli,lli);
lli moduloSub(lli,lli);
lli moduloMul(lli,lli);
lli recFib(lli);
lli itrFib(lli);

int main(int argc, char const *argv[])
{
    cin>>m;
    cout<<itrFib(m);
    return 0;
}


lli moduloSub(lli a,lli b){
    if(a>=b){
        return a-b;
    }
    else{
        return (a+m)-b;
    }
}

lli moduloAdd(lli a,lli b){
    return ((a%m)+(b%m))%m;
}

lli moduloMul(lli a,lli b){
    return ((a%m)*(b%m))%m;
}

lli recFib(lli x){
    if(x<=1)
        return x;
    else{
        return (recFib(x-1)+recFib(x-2))%m;
    }
}

lli itrFib(lli x){
    lli f0=0,f1=1,res=0;
    for(lli i=1;i<x;i++){
        res=moduloAdd(f0,f1);
        f0=f1;
        f1=res;
        // cout<<res<<endl;
    }
    return res;
}