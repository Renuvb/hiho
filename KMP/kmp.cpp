//
// Created by xiejiaqi.01 on 2018/4/6.
//
// http://hihocoder.com/problemset/problem/1015

#include <string>
#include <iostream>
#include <vector>

// next数组 next[i] = max{k-1 | 0<=k<i && str[0:k] == str[i-k:i] }
// next数组的含义是 next[i] = k 在第i个位置，向前数k个字母，和该字符串从头数k个字母可以匹配
void buildNext(const std::string& pattern, std::vector<int> &next) {
    next.resize(pattern.size());
    next[0] = 0;
    int matchLen = 0;
    for (int i=1;i<pattern.size();i++) {
        while (matchLen > 0 && pattern[i] != pattern[matchLen]) {
            matchLen = next[matchLen-1];
        }
        if (pattern[matchLen] == pattern[i]) {
            matchLen++;
        }
        next[i] = matchLen;
    }
}

int findPatternCount(const std::string& baseStr, const std::string& pattern) {
    std::vector<int> next;
    buildNext(pattern, next);
    int patternIndex = 0;
    int resultCount = 0;
    for (int i=0;i<baseStr.size();i++) {
        while(patternIndex != 0 && pattern[patternIndex] != baseStr[i]) {
            patternIndex = next[patternIndex-1];
        }
        if (baseStr[i] == pattern[patternIndex]) {
            patternIndex++;
            if (patternIndex == pattern.size()) {
                resultCount++;
                patternIndex = next[patternIndex-1];
            }
        }
    }
    return resultCount;
}

int main() {
    int n;
    std::string baseStr, pattern;
    std::cin >> n;
    for (int i=0;i<n;i++) {
        std::cin >> pattern;
        std::cin >> baseStr;
        std::cout << findPatternCount(baseStr, pattern) << std::endl;
    }
    return 0;
}