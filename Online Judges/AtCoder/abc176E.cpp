#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int n, m, targets;
int cntRow[maxN];
vector<int> rows[maxN];

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{max(value, other.value)};
  }
};
const Data nil = Data{0};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size);
    st.resize(4*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { if (qlo < 0) qlo = 0; if (qhi < qlo) return nil; return query(qlo, qhi, 1, 0, size - 1); }
  void update(int pos, T value) { update(pos, value, 1, 0, size - 1); }
  void build(int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};

int main()
{
  while (scanf("%d %d %d", &n, &m, &targets) != EOF)
  {
    for (int i = 0; i < n; i++) rows[i].clear();
    memset(cntRow, 0, sizeof(cntRow));
    Segtree<Data> columnSegtree = Segtree<Data>(m + 1, nil);
    // int hehe[n][m]; memset(hehe, 0, sizeof(hehe));
    for (int k = 0; k < targets; k++)
    {
      int i, j; scanf("%d %d", &i, &j); i--, j--;
      cntRow[i]++, columnSegtree.data[j].value++;
      rows[i].push_back(j);
      // hehe[i][j]++;
    }
    columnSegtree.build();
    for (int i = 0; i < n; i++)
    {
      rows[i].push_back(m);
      sort(rows[i].begin(), rows[i].end());
    }

    // for (int i = 0; i < n; i++)
    // {
    //   for (int j = 0; j < m; j++)
    //     printf("%d", hehe[i][j]);
    //   printf("\n");
    // }

    int maxRow = *max_element(cntRow, cntRow+n), maxColumn = 0;

    for (int i = 0; i < n; i++)
    {
      if (cntRow[i] == maxRow)
      {
        int lo = -1, hi = -1;
        for (int j = 0; j < rows[i].size(); j++)
        {
          hi = rows[i][j] - 1;
          DEBUG printf("\tranges %d: %d %d - %d\n", i, lo, hi, columnSegtree.query(lo, hi).value);
          maxColumn = max(maxColumn, columnSegtree.query(lo, hi).value);

          int jj = j;
          while (jj + 1 < rows[i].size() && rows[i][jj + 1] == rows[i][jj] + 1)
            jj++;
          lo = rows[i][jj] + 1;
          j = jj;
        }
      }
    }
    int ans = maxRow + max(maxColumn, columnSegtree.query(0, m - 1).value - 1);
    printf("%d\n", ans);
  }
  return 0;
}