#include<iostream>
using namespace std;
#define SIZE 1024

int skip(int&,char[]);

int main(int argc, char const *argv[])
{
    char str[SIZE];
    cout<<"\n\n\n\033[1;32m--------------WORD COUNT----------------\033[0m\n\n";
    cout<<"ENTER TEXT : \n",cin.getline(str,SIZE,'$');

    int count=1,j=0;
    for(int i=0;str[i]!='\0';i++){
        j=i;
        if(skip(i,str)!=j && str[j+1]!='\0' && str[i]!='\0')
            count++;    
    }

    cout<<"\n\033[1;32m------------------------------------------\033[0m\n";
    cout<<"\033[1;31mWORD COUNT : "<<count<<"\033[0m";
    cout<<"\n\033[1;32m------------------------------------------\033[0m\n\n";
    return 0;
}

int skip(int &i,char str[]){
    if(str[i]!=' ' && str[i]!='\n' && str[i]!='\t' && str[i]!=',' && str[i]!='.')
        return i;
    else{
        i++;    
        return skip(i,str);
    }    
}