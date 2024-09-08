#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n;
char ss[kMaxN + 1];
string s[kMaxN];
int cnt[kMaxN];

string ReadString() {
  scanf(" %s", ss);
  return string(ss);
}

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i)
      s[i] = ReadString();

    fill(cnt, cnt+n, 0);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        cnt[i] += s[i][j] == 'o';

    vector<pair<int, int>> players;
    for (int i = 0; i < n; ++i)
      players.emplace_back(cnt[i], -i);
    sort(players.begin(), players.end(), greater<pair<int, int>>());

    for (int i = 0; i < n; ++i)
      printf("%d%c", -players[i].second + 1, i + 1 < n ? ' ' : '\n');
  }
  return 0;
}
