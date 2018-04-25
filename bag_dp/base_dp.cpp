//
// Created by xiejiaqi.01 on 2018/4/25.
//

#include <iostream>
#include <vector>

using namespace std;

const int maxn = 505;
int need[maxn], value[maxn];
const int maxm = 100005;
int best[maxm];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i=0;i<n;i++) {
        cin >> need[i] >> value[i];
    }
    for (int i=0;i<=m;i++) {
        best[i] = 0;
    }
    for (int i=0;i<n;i++) {
        for (int j=m;j>=need[i];j--) {
            best[j] = max(best[j], best[j-need[i]] + value[i]);
        }
    }
    cout << best[m] << endl;
    return 0;
}