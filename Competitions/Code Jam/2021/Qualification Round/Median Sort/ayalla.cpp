#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 998244353

struct Triple
{
  int a, b, c;
  bool operator<(const Triple &other) const { return a < other.a || (a == other.a && b < other.b) || (a == other.a && b == other.b && c < other.c); }
};
map<Triple, int> memo;

int query(int i, int j, int k)
{
  vector<int> abc = {i, j, k};
  sort(abc.begin(), abc.end());
  Triple triple = Triple{abc[0], abc[1], abc[2]};
  if (memo.count(triple))
    return memo[triple];

  cout << i + 1 << " " << j + 1 << " " << k + 1 << endl;
  fflush(stdout);
  int ans;
  cin >> ans;
  ans--;
  return memo[triple] = ans;
}

bool print(vector<int> ans)
{
  for (auto const &i : ans)
    cout << i + 1 << " ";
  cout << endl;
  fflush(stdout);
  int ok;
  cin >> ok;
  return (ok == 1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, n, q;
  cin >> t >> n >> q;
  while (t--)
  {
    memo.clear();
    int ini = query(0, 1, 2);
    vector<int> ans;
    if (ini == 0)
      ans = {1, 0, 2};
    else if (ini == 1)
      ans = {0, 1, 2};
    else
      ans = {0, 2, 1};

    vector<int> aux;
    for (int i = 3; i < n; i++)
      aux.push_back(i);
    // unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    // default_random_engine e(seed);
    // shuffle(aux.begin(), aux.end(), e);

    for (int ii = 3; ii < n; ii++)
    {
      int i = aux[ii - 3];
      int l = 0, r = ans.size() - 1;
      bool added = false;
      while (l < r - 2)
      {
        int midlo = (2*l + r) / 3, midhi = (l + 2*r) / 3;
        int curr = query(ans[midlo], i, ans[midhi]);
        if (curr == i && r - l + 1 == 3)
        {
          int idx = midlo + 1;
          ans.insert(ans.begin() + idx, i);
          added = true;
          break;
        }
        else if (curr == ans[midlo]) r = midlo;
        else if (curr == ans[midhi]) l = midhi;
        else l = midlo, r = midhi;
      }

      if (!added)
        while (l < r)
        {
          int mid = (l + r) >> 1;
          int curr = query(ans[mid], i, ans[mid + 1]);
          if (curr == i)
          {
            int idx = mid + 1;
            ans.insert(ans.begin() + idx, i);
            added = true;
            break;
          }
          if (curr == ans[mid])
            r = mid;
          else
            l = mid + 1;
        }

      if (!added)
        (!l) ? ans.insert(ans.begin() + 0, i) : ans.insert(ans.end(), i);
    }
    int ok = print(ans);
    if (!ok)
      return 0;
  }
  return 0;
}
// query(1, 2, 3)
// vou saber a ordem dos 3 caras iniciais
// de resto
// adicionando de um por um
// faco uma busca binaria para saber o indice do novo cara
// quando eu acho um cara tal que query(v[mid], curr, v[mid + 1]) == curr
// eu posso por o novo cara ali
// se eu nao achar na bb
// ele pode tar no inicio ou no fim