#include <bits/stdc++.h>
using namespace std;

const int maxn = 250;

struct pt { double x, y; };

inline double dis(const pt& a, const pt& b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double dist[maxn][maxn];
double dp[maxn][maxn];
pt p[maxn];
int n;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	cin >> n;
	n <<= 1;

	for (int i = 0; i < n; ++i) {
		cin >> p[i].x >> p[i].y;
	}

	for (int i = 0; i < n-1; ++i) {
		dist[i][i] = dist[i][i+1] = 0.0;
		for (int j = i + 2; j < n; ++j) {
			dist[i][j] = dis(p[i], p[j]);
		}
	}

	for (int sz = 1; sz <= n; ++sz) {
		for (int i = 0; i+sz <= n; ++i) {
			int j = i+sz-1;
			if (j-i+1 < 4) {
				if (j-i == 1) dp[i][j] = 0;
				else dp[i][j] = 1e12; 
			} else {
				double ans = 1e12;
				for (int a = i+1; a <= j-2; ++a) {
					for (int b = a+1; b <= j-1; ++b) {
						ans = min(ans, dp[i][a] + dp[a][b] + dp[b][j] + dist[i][a] + dist[a][b] + dist[b][j]);
					}
				}
				dp[i][j] = ans;
			}
		} 
	}

	cout << fixed << setprecision(4);
	cout << dp[0][n-1] << '\n';

	return 0;
}