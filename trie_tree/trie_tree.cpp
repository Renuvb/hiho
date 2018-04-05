//
// Created by xiejiaqi.01 on 2018/4/5.
//

#include <string>
#include <map>
#include <iostream>

class TrieTree {
private:
    struct TrieTreeNode {
        char ch;
        std::map<char, TrieTreeNode*> childMap;
        int count;
    };
public:
    TrieTree(){
        rootNode.ch = 0;
        rootNode.count = 0;
    }
    void addWord(const std::string& word) {
        TrieTreeNode *curNode = &rootNode;
        curNode->count++;
        for (int i=0;i<word.size();i++) {
            auto ite = curNode->childMap.find(word[i]);
            if (ite == curNode->childMap.end()) {
                TrieTreeNode* newNode = new TrieTreeNode;
                newNode->ch = word[i];
                newNode->count = 1;
                curNode->childMap[word[i]] = newNode;
                curNode = newNode;
            } else {
                ite->second->count++;
                curNode = ite->second;
            }
        }
    }

    int find_prefix_count(const std::string& word) {
        TrieTreeNode* curNode = &rootNode;
        for (int i=0;i<word.size();i++) {
            auto ite = curNode->childMap.find(word[i]);
            if (ite == curNode->childMap.end()) {
                return 0;
            } else {
                curNode = ite->second;
            }
        }
        return curNode->count;
    }
private:
    TrieTreeNode rootNode;
};


int main() {
    int n, m;
    TrieTree tt;
    std::cin >> n;
    std::string word;
    for (int i=0;i<n;i++) {
        std::cin >> word;
        tt.addWord(word);
    }
    std::cin >> m;
    for (int i=0;i<m;i++) {
        std::cin >> word;
        std::cout << tt.find_prefix_count(word) << std::endl;
    }
    return 0;
}