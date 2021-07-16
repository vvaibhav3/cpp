class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        
        int start=0,end=1;
        
        //contains elements in ascendig order
        set<pair<int,int>> max_elements;
        
        //to store answer
        vector<int> answer;
        
        //k==1 then the single element is max whithin window
        if(k==1){
            return nums;
        }
        
        //intial values
        max_elements.insert({nums[0],0});
        auto temp=max_elements.begin();
        
        while(end<nums.size()){
            
            if(((*temp).first)<nums[end]){
                max_elements.clear();
                max_elements.insert({nums[end],end});
                temp=max_elements.begin();
            }
            else
                max_elements.insert({nums[end],end});
            
            //window size encountered
            if((end-start+1)==k){
                
                //add max to answer
                answer.emplace_back((*temp).first);
                
                //if set is not empty then remove element from set and update max
                if(max_elements.size()>0){
                    max_elements.erase({nums[start],start});
                    temp=max_elements.end();
                    temp--;
                }
                   
                start++;
            }
            end++;
        }
        
        return answer;
    }
};