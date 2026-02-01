class TrieNode {
public:
    TrieNode* next[2] = {};
    bool end = false;
    int idx = -1;
};
 
class Trie {
    TrieNode* root = new TrieNode;
public:
    void insert(int num, int idx) {
        TrieNode* cur = root;
        for(int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!cur->next[bit]) cur->next[bit] = new TrieNode;
            cur = cur->next[bit];
        }
        cur->end = true;
        cur->idx = idx;
    }
    pii query(int num){
        TrieNode* cur = root;
        int ans = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int op = bit ^ 1;
            if (cur->next[op]) {
                ans |= (1 << i);   // we can get 1 in this bit of XOR
                cur = cur->next[op];
            } 
            else {
                cur = cur->next[bit];  // must take same bit XOR bit is 0
            }
        }
        return {ans,cur->idx};
 
    }
};  