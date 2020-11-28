#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  vector<int> values;
  Data operator+(const Data &other)
  {
    Data ans = Data{};
    ans.values.resize(values.size() + other.values.size());
    merge(values.begin(), values.end(), other.values.begin(), other.values.end(), ans.values.begin());
    return ans;
  }
  void put(Data &other)
  {
    for (int i: other.values)
      values.push_back(i);
  }
};
Data nil = Data{{}};

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
  T query(lli yMin, int qlo, int qhi)
  {
    T ans;
    query(ans, yMin, qlo, qhi, 1, 0, size - 1);
    sort(ans.values.begin(), ans.values.end()); // optional
    return ans;
  }
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
  void query(T &ans, lli yMin, int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return;
    if (lo >= qlo && hi <= qhi) return ans.put(st[i]);
    int mid = (lo + hi) >> 1;
    query(ans, yMin, qlo, qhi, 2*i, lo, mid);
    query(ans, yMin, qlo, qhi, 2*i + 1, mid + 1, hi);
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
  
  return 0;
}