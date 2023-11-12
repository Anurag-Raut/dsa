class Node {
public:
    Node* one;
    Node* zero;
};
 
class trie {
    Node* root;
 
public:
    trie() { root = new Node(); }
 
    void insert(int n)
    {
        Node* temp = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (bit == 0) {
                if (temp->zero == NULL) {
                    temp->zero = new Node();
                }
                temp = temp->zero;
            }
            else {
                if (temp->one == NULL) {
                    temp->one = new Node();
                }
                temp = temp->one;
            }
        }
    }
 
    int max_xor_helper(int value)
    {
        Node* temp = root;
        int current_ans = 0;
 
        for (int i = 31; i >= 0; i--) {
            int bit = (value >> i) & 1;
            if (bit == 0) {
                if (temp->one) {
                    temp = temp->one;
                    current_ans += (1 << i);
                }
                else {
                    temp = temp->zero;
                }
            }
            else {
                if (temp->zero) {
                    temp = temp->zero;
                    current_ans += (1 << i);
                }
                else {
                    temp = temp->one;
                }
            }
        }
        return current_ans;
    }
     Node* deleteNode(Node* temp,int n,int i=31)
    {
        if(i<0){
            
            return NULL;
        }
       
            int bit = (n >> i) & 1;
         
            if (bit == 0) {
                if (temp->zero != NULL) {
                       temp->zero=deleteNode(temp->zero,n,i-1);
                }
                
            }
            else {
                if (temp->one != NULL) {
                   temp->one=deleteNode(temp->one,n,i-1);
                }
             
            }
        if(temp->zero==NULL && temp->one==NULL){
            return NULL;
        }
        return temp;
    }
 
    int max_xor(vector<int> &arr, int n)
    {
        int max_val = 0;
        int j=0;
        
         for(int i=0;i<n;i++){
            insert(arr[i]);
            while( arr[j]*2<arr[i]){
                // cout<<arr[j]<<endl;
                deleteNode(root,arr[j]);
                j++;
            }
            cout<<max_xor_helper(arr[i])<<endl;
            max_val=max(max_val,max_xor_helper(arr[i]));
        }
        return max_val;
    }
};
class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
       sort(nums.begin(),nums.end());
        int ans=0;
        int n=nums.size();
        unordered_map<int,int> vis;
        vector<int> newNums;
        for(int i=0;i<n;i++){
            if(!vis[nums[i]]){
                newNums.push_back(nums[i]);
                
            }
            vis[nums[i]]=1;
        }
        n=newNums.size();
        trie t;
        sort(newNums.begin(),newNums.end());
        ans=t.max_xor(newNums,n);
      
        
        return ans;
        
    }
};
