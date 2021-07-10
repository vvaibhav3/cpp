    
    //sliding window
    #include<bits/stdc++.h>
    using namespace std;
    
    vector<int> findAnagrams(string s, string p) {
        
        //to store all starting index of anagrams
        vector<int> answer;
        
        //if size of p and s are equal and p=s then return 0 index as start
        if(p.size()==s.size())
            if(p==s){
                answer.push_back(0);
                return answer;
            }
        
        //two pointer for start and end of s
        int start=0,end=0;
        
        //to store count of every unique char in p
        unordered_map<char,int> char_count;
        
        //get count of every char in p
        while(start<p.size()){
            char_count[p[start]]++;
            start++;
        }
        
        start=0;
        
        //no of unique char in p
        int count=char_count.size();
        
        //scan s and process
        while(end<s.size()){
            
            //if char is in p then dec count of char and if all char's are present in window
            //char_count=0 then all no of particuler char is present then reduce one count that indicates one char is available in p
            if(char_count.count(s[end])!=0){
                char_count[s[end]]--;
                
                if(char_count[s[end]]==0)
                    count--;
            }
            
            //if window size encountered i.e substring length exhausted
            if((end-start+1)==p.size()){
                
                //p is present in s then store index
                if(count==0)
                    answer.push_back(start);
                
                //exclude start (if char is from p) and move window - i.e take next char from s
                if(char_count.count(s[start])!=0){
                    char_count[s[start]]++;

                    //if count of any char become 1 from 0 then 1 more match for char required so inc count
                    if(char_count[s[start]]==1)
                        count++;
                }
                start++;
             }
            
            end++;
                           
            }
            
            return answer;
    }

    int main(int argc, char const *argv[])
    {
        string s,p;
        cout<<"Input : \n";
        cout<<"first line contains two strings s and p \n";
        cin>>s>>p;

        vector<int> ans;
        ans=findAnagrams(s,p);

        for(auto o:ans){
            cout<<o<<"\t";
        }
        cout<<endl;

        return 0;
    }
    