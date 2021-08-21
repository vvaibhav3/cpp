#include<iostream>
#include<cmath>
using namespace std;

int main(int argc, char const *argv[])
{

    int n;
    cin>>n;
    int digit=floor(log(n)/log(10));
    
    if(n<0 || n>1000000){
        cout<<"Wrong input\n";
        return 1;
    }
    int divider=pow(10,digit);
    int result=0,temp=0;
    while(n>0){
        temp=(n/divider);
        result+=(10-temp-1)*divider;
        n=n%divider;
        divider/=10;
    }
    cout<<endl;
    cout<<result<<endl;
    return 0;
}
