#include<iostream>
using namespace std;

int recGCD(int,int);
int itrGCD(int,int);

int main(int argc, char const *argv[])
{
    int a,b;
    cout<<"\n\n\n\n\033[1;32m-----------------Eculids Algo For GCD--------------------\n\033[0m";
    
    cout<<"\n\033[1;31mA: ",cin>>a;
    cout<<"\nB: ",cin>>b;

    cout<<"\nRecursive : "<<recGCD(a,b)<<endl;
    
    cout<<"\nIterative : "<<itrGCD(a,b)<<endl;

    cout<<"\n\033[1;32m---------------------------------------------------------\n\033[0m\n\n";

    return 0;
}

int recGCD(int a,int b){
    if(b==0) return a;
    return recGCD(b,a%b);
}

int itrGCD(int a,int b){
    int temp;
    while(b>0){
        temp=a;
        a=b;
        b=temp%b;
    }
    return a;
}

//a=140,b=12 
//140=12*11+8       ------------------A=B*q+r
//12=8*1+4
//8=4*2+0
//a=4 , b=0


//24































// cout<<a%0; floating point exceptiom
