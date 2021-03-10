#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int cnt, value;
  Data operator+(const Data &other)
  {
    if (cnt == 0 && other.cnt == 0)
      return value < other.value ? *this: other;
    if (cnt == 0)
      return *this;
    if (other.cnt == 0)
      return other;
    return *this;
  }
};
const Data nil = Data{1, (int)1e9};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() { }
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size, nil);
    st.resize(4*size, nil);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
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
      // st[i] = data[lo] = value;
      st[i].cnt += value.cnt;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

const int maxN = 1500000; int n, m;
int a[maxN];
int cnt[maxN + 1];

// set<int> zeros;
// void setUpdate(int value, int delta)
// {
//   if (delta == 1)
//   {
//     if (cnt[value] == 0)
//       zeros.erase(value);
//   }
//   else
//   {
//     if (cnt[value] == 1)
//       zeros.insert(value);
//   }
//   cnt[value] += delta;
// }

priority_queue<int, vector<int>, greater<int>> zeros;
bool removed[maxN + 1];
void priorityQueueUpdate(int value, int delta)
{
  if (delta == 1)
  {
    if (cnt[value] == 0)
      removed[value] = true;
  }
  else
  {
    if (cnt[value] == 1)
      zeros.push(value);
  }
  cnt[value] += delta;
}
int priorityQueueQuery()
{
  while (true)
  {
    int ans = zeros.top();

    if (removed[ans])
    {
      removed[ans] = false;
      zeros.pop();
    }
    else
      return ans;
  }
  return -1;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    segtree = Segtree<Data>(maxN + 1, nil);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int ans = 1e9;

    // Segtree solution
    // for (int i = 0; i <= maxN; i++)
    //   segtree.data[i] = Data{0, i};
    // segtree.build();
    // for (int i = 0; i < m; i++)
    //   segtree.update(a[i], Data{1, 0});

    // for (int i = 0; i + m - 1 < n; i++)
    // {
    //   // [i : i + m - 1]
    //   ans = min(ans, segtree.query(0, maxN).value);
    //   segtree.update(a[i], Data{-1, 0});
    //   if (i + m < n) segtree.update(a[i + m], Data{1, 0});
    // }

    // Set solution
    // for (int i = 0; i <= maxN; i++)
    //   zeros.insert(i);
    // memset(cnt, 0, sizeof(cnt));
    // for (int i = 0; i < m; i++)
    //   setUpdate(a[i], 1);

    // for (int i = 0; i + m - 1 < n; i++)
    // {
    //   // [i : i + m - 1]
    //   ans = min(ans, *zeros.begin());
    //   setUpdate(a[i], -1);
    //   if (i + m < n) setUpdate(a[i + m], 1);
    // }

    // Priority Queue solution
    while (!zeros.empty())
      zeros.pop();
    for (int i = 0; i <= maxN; i++)
      zeros.push(i);
    memset(cnt, 0, sizeof(cnt));
    memset(removed, false, sizeof(removed));
    for (int i = 0; i < m; i++)
      priorityQueueUpdate(a[i], 1);

    for (int i = 0; i + m - 1 < n; i++)
    {
      // [i : i + m - 1]
      ans = min(ans, priorityQueueQuery());
      priorityQueueUpdate(a[i], -1);
      if (i + m < n) priorityQueueUpdate(a[i + m], 1);
    }
    printf("%d\n", ans);
  }
  return 0;
}