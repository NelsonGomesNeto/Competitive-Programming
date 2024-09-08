#include<bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    vector<bool> used(n - m + 1);
    queue<int> q;
    auto check = [&](int i) {
        if (used[i]) return;
        bool ok = true;
        for (int j = 0; j < m; j++) {
            ok &= (s[i + j] == '#' or s[i + j] == t[j]);
        }
        if (ok) {
            used[i] = true;
            q.push(i);
        }
    };
    for (int i = 0; i < n - m + 1; i++) check(i);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j = 0; j < m; j++) s[i + j] = '#';
        for (int j = max(i - m + 1, 0); j <= min(i + m - 1, n - m); j++) {
            check(j);
        }
    }
    cout << (s == string(n, '#') ? "Yes" : "No") << endl;
}
