#include<bits/stdc++.h>
using namespace std;

int KMP(string patt,string str){


    //Building Reset Table

    //reset table to reset ptr of pattern when there is no match
    //so we can avoid intermediate part
    vector<int> reset(patt.size(),0);

    //first index will have no reset value since there is nothing to point at prev
    reset[0]=-1;

    //initialy ptrs both are pointing in pattern array
    int j=-1,i=0;

    //till the end of patt
    while(i<patt.size()){

        //check if j and i are equal if not then reset j pointer
        while(j>=0 and patt[j]!=patt[i])
            j=reset[j]; // j will be pointing reset index from current index reset value

        //incr ptrs for next char
        i++;j++;

        //store value of j at ith index for reset
        reset[i]=j;
    }

    //printing reset table
    cout<<"Reset table : "<<endl;
    for(auto r:reset){
        cout<<r<<"\t";
    }
    cout<<endl;


    //Now matching pattern in given string will be almost everything same 
    //just counter for result and check pattern exhausted

    //to store no of times pattern matched in given string
    int count=0;

    //initializing ptr , i is pointing to str and j is pointing to patt
    i=0,j=0;

    //till the end of str find pattern
    while(i<str.size()){

        while(j>=0 and patt[j]!=str[i])
            j=reset[j];
        
        i++,j++;
        
        //if j = pattlen then pattern is found incr count
        //reset j to reset[j-1] for again pattern match
        //dec i by 1 since to avoid prev i++ effect same for j-1
        if(j==patt.size()){
            count++;
            j=reset[j-1];
            i-=1;
        }

    }

    cout<<count<<endl;

    return count;
}

int main(){

    //str = to hold string in which we want to find pattern
    //patt = to find pattern in given string
    string str,patt;

    cin>>str>>patt;

    KMP(patt,str);

    return 0;
}