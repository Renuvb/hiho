//
// Created by xiejiaqi.01 on 2018/4/13.
//

#include <map>
#include <list>
#include <iostream>
#include <set>

using namespace std;

struct TrieNode{
    bool leafFlag;
    TrieNode *next;
    TrieNode *childNodeList[26];

    TrieNode()
            :leafFlag(false),
             next(NULL)
    {
        for (int i=0;i<26;i++) {
            childNodeList[i] = NULL;
        }
    }
};

TrieNode rootNode;

void addNode(const std::string& str) {
    TrieNode *curNode = &rootNode;
    for (int i=0;i<str.size();i++) {
        char ch = str[i];
        TrieNode *childNode = curNode->childNodeList[ch - 'a'];
        if (childNode == NULL) {
            childNode = new TrieNode();
            curNode->childNodeList[ch - 'a'] = childNode;
        }
        curNode = childNode;
    }
    curNode->leafFlag = true;
}

void initial() {
    list<TrieNode*> nodeList;
    rootNode.next = &rootNode;
    for (auto childNode : rootNode.childNodeList) {
        if (childNode == NULL) {
            continue;
        }
        nodeList.push_back(childNode);
        childNode->next = &rootNode;
    }
    while(!nodeList.empty()) {
        TrieNode *frontNode = nodeList.front();
        nodeList.pop_front();

        for (auto childNode : frontNode->childNodeList) {
            if (childNode != NULL) {
                nodeList.push_back(childNode);
            }
        }

        if (frontNode->next == NULL) {
            frontNode->next = &rootNode;
        }
        TrieNode *curNext = frontNode->next;
        for (int i=0;i<26;i++) {
            if (curNext->childNodeList[i] == NULL) {
                continue;
            }
            if (frontNode->childNodeList[i] != NULL) {
                frontNode->childNodeList[i]->next = curNext->childNodeList[i];
                if (curNext->childNodeList[i]->leafFlag) {
                    frontNode->childNodeList[i]->leafFlag = true;
                }
            } else {
                frontNode->childNodeList[i] = curNext->childNodeList[i];
            }
        }
    }
}

bool match(const string &s) {
    TrieNode *curNode = &rootNode;
    for (char ch : s) {
        if (curNode->childNodeList[ch - 'a'] != NULL) {
            curNode = curNode->childNodeList[ch - 'a'];
        } else {
            curNode = &rootNode;
        }
        if (curNode->leafFlag) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        addNode(str);
    }
    initial();
//    cout << "finish initial" << endl;
    string s;
    cin >> s;
    if (match(s))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}