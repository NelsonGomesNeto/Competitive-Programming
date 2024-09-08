#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
int a[maxN];
int biggestCompression[maxN];

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{min(value, other.value)};
  }
};
const Data nil = Data{maxN + 1};

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
    data.resize(size);
    st.resize(4*size);
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
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> aseg, kseg;

bool can(int i, int k)
{
  int lo = 0, hi = k;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    int kl = mid, kr = k - mid;
    if (i - kl >= 0 && i + kr < n && aseg.query(i - kl, i + kr).value == a[i]) return true;
    swap(kl, kr);
    if (i - kl >= 0 && i + kr < n && aseg.query(i - kl, i + kr).value == a[i]) return true;

    hi = mid;
  }
  return false;
  int mid = k >> 1, midu = (k + 1) >> 1;
  return (i - k >= 0 && aseg.query(i - k, i).value == a[i])
      || (i + k < n && aseg.query(i, i + k).value == a[i])
      // || (i - mid >= 0 && i + midu < n && aseg.query(i - mid, i + midu).value == a[i])
      || (i - midu >= 0 && i + mid < n && aseg.query(i - midu, i + mid).value == a[i]);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    aseg = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      aseg.data[i] = Data{a[i]};
    aseg.build();

    memset(biggestCompression, -1, sizeof(biggestCompression));
    for (int i = 0; i < n; i++)
      biggestCompression[a[i]] = maxN + 1;
    for (int i = 0; i < n; i++)
    {
      // left
      int lo = 0, hi = i;
      while (lo < hi)
      {
        int mid = (lo + hi + 1) >> 1;
        if (aseg.query(i - mid, i).value == a[i]) lo = mid;
        else hi = mid - 1;
      }
      int left = i - lo;
      lo = 0, hi = n - i - 1;
      while (lo < hi)
      {
        int mid = (lo + hi + 1) >> 1;
        if (aseg.query(i, i + mid).value == a[i]) lo = mid;
        else hi = mid - 1;
      }
      int right = i + lo;
      DEBUG printf("\t%d %d - %d %d\n", i, a[i] + 1, left, right);
      biggestCompression[a[i]] = min(biggestCompression[a[i]], right - left);
    }

    kseg = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
      kseg.data[i] = Data{biggestCompression[i]};
    kseg.build();

    string ans = "";
    for (int i = 0; i < n; i++) ans += '0';

    for (int i = 0; i < n; i++)
    {
      // for i to appear in the permutation
      // there will need to be a n - i compression
      // if there can't be a n - i compression: all other compressions will fail
      // except 1-compression, if a is a permutation it self

      int k = n - i - 1;
      int smallest = kseg.query(0, i).value;
      DEBUG {
        printf("\t%d-compression, biggestValue: %d, smallest-compression: %d\n", k, i + 1, smallest);
        for (int j = 0; j <= i; j++)
          printf("(%d, %d)%c", j + 1, biggestCompression[j], j < i ? ' ' : '\n');
      }
      ans[k] = smallest >= k ? '1' : '0';
    }

    printf("%s\n", ans.c_str());
  }
  return 0;
}
