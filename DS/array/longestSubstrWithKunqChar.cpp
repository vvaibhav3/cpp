//variable size sliding window

#include<bits/stdc++.h>
using namespace std;

int longestSubtr(string &s,int k){

    int ans=0,end=0,start=0;
    unordered_map<char,int> charCount;

    for(end=0;end<s.size();end++){

        charCount[s[end]]+=1;

        if(charCount.size()==k){
            ans=max(ans,end-start+1);
        }
        else if(charCount.size()>k){
            while(charCount.size()>k){
                charCount[s[start]]-=1;
                if(charCount[s[start]]==0)
                    charCount.erase(s[start]);

                start++;
            }
        }

    }

    return ans;
}

int main(int argc, char const *argv[])
{
    string s;
    int k;
    cout<<"Input : \n";
    cout<<"First line will contain string s \n";
    cout<<"Second line will k integer - no of char\n";
    
    cin>>s>>k;

    cout<<longestSubtr(s,k);

    return 0;
}
