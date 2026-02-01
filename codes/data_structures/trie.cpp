#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* next[26] = {};
    bool end = false;
};

class Trie {
    TrieNode* root = new TrieNode;
public:
    void insert(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int i = c - 'a';
            if (!cur->next[i]) cur->next[i] = new TrieNode;
            cur = cur->next[i];
        }
        cur->end = true;
    }

    bool search(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int i = c - 'a';
            if (!cur->next[i]) return false;
            cur = cur->next[i];
        }
        return cur->end;
    }
    bool starts_with(const string& prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!cur->next[i]) return false;
            cur = cur->next[i];
        }
        return true;
    }
};
