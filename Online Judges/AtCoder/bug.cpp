#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <forward_list>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef bitset<16> BS;
struct edge {
    int to, cost, id;
};
const double EPS = 1E-09;
const ll MOD = 1E+09 + 7; // =998244353;
const ll INF = 1E18;
const int MAX_N = 2E+05;

ll dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

string N;
int K;

ll dp[MAX_N + 1][17];
bool check[16];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N >> K)
    {
      memset(memo, 0, sizeof(memo));
      int sp = 0;
      for (ll i = 0; i < N.size(); i++) {
          for (ll j = 1; j <= 16; j++) {
              dp[i + 1][j] += dp[i][j] * j;
              dp[i + 1][j] %= MOD;
              if (j < 16) {
                  dp[i + 1][j + 1] += dp[i][j] * (16 - j);
                  dp[i + 1][j + 1] %= MOD;
              }
          }
          for (int c = 0; c < stoi(string { N[i] }, nullptr, 16); c++) {
              if (i == 0 && c == 0)
                  continue;
              if (!check[c]) {
                  dp[i + 1][sp + 1] += 1;
                  dp[i + 1][sp + 1] %= MOD;
              } else {
                  dp[i + 1][sp] += 1;
                  dp[i + 1][sp] %= MOD;
              }
          }

          if (i > 0) {
              dp[i + 1][1] += 15;
              dp[i + 1][1] %= MOD;
          }

          int c = stoi(string { N[i] }, nullptr, 16);
          if (!check[c]) {
              sp++;
              check[c] = true;
          }
      }

      // for (int i = 0; i <= N.size(); i++) {
      //     for (int j = 0; j <= 16; j++) {
      //         cout << "i = " << i << ", j = " << j << ", dp = " << dp[i][j] << "\n";
      //     }
      // }

      ll ans = dp[N.size()][K];
      if (sp == K) {
          ans++;
          ans %= MOD;
      }

      cout << ans << "\n";
    }


    return 0;
}