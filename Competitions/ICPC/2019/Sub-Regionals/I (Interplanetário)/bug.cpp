#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 401
#define mod 1000000007
#define INF 1e7

int n, m;
pi v[MAXN];
int eq[MAXN];
int eq2[MAXN];
int d[MAXN][MAXN][MAXN];
int d2[MAXN][MAXN][MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir;
    v[i].sec = i;
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      d[i][j][0] = (i == j) ? 0 : INF;
      d2[i][j][0] = (i == j) ? 0 : INF;
    }
  }
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    // para k = 0, vc so pode passar de a ate b se existir uma aresta entre eles
    d[a][b][0] = c;
    d[b][a][0] = c;
    d2[a][b][0] = c;
    d2[b][a][0] = c;
  }
  sort(v, v + n); // ordeno as temperaturas
  int ptr = 0;
  for (int i = 1; i <= n; i++)
  {
    int ini = v[ptr].fir;
    // se varios planetas tem temperaturas iguais, um mesmo k vale pra todos eles
    while (ptr + 1 < n && v[ptr + 1].fir == ini)
      ptr++;
    eq[i] = ptr + 1;
    ptr = min(ptr + 1, n - 1);
  }
  ptr = n - 1;
  for (int i = 1; i <= n; i++)
  {
    int ini = v[ptr].fir;
    // se varios planetas tem temperaturas iguais, um mesmo k vale pra todos eles
    while (ptr - 1 >= 0 && v[ptr - 1].fir == ini)
      ptr--;
    eq2[i] = n - ptr;
    ptr = max(ptr - 1, 0);
  }
  for (int i = 1; i <= n; i++)
  {
    // o i-esimo mais frio
    int l = v[i - 1].sec;
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        d[j][k][i] = min(d[j][k][i - 1], d[j][l][i - 1] + d[l][k][i - 1]);
    // a distancia entre 2 vertices j e k, ira diminuir se eu posso ir de j para o
    // i-esimo mais frio e em seguida ir para k com uma distancia menor
  }
  for (int i = 1; i <= n; i++)
  {
    // o i-esimo mais quente
    int l = v[n - i].sec;
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        d2[j][k][i] = min(d2[j][k][i - 1], d2[j][l][i - 1] + d2[l][k][i - 1]);
    // a distancia entre 2 vertices j e k, ira diminuir se eu posso ir de j para o
    // i-esimo mais quente e em seguida ir para k com uma distancia menor
  }
  int q;
  cin >> q;
  while (q--)
  {
    int a, b, c, t;
    cin >> a >> b >> c >> t;
    a--, b--;
    if (!t)
      (d[a][b][eq[c]] == INF) ? cout << -1 << endl : cout << d[a][b][eq[c]] << endl;
    else
      (d2[a][b][eq2[c]] == INF) ? cout << -1 << endl : cout << d2[a][b][eq2[c]] << endl;
  }
}