#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
};
const Data nil = Data{0};

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
    st.resize(2*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(2*size);
    build();
  }
  void build()
  {
    for (int i = 0; i < size; i++) st[size + i] = data[i];
    for (int i = size - 1; i; i--) st[i] = st[2*i] + st[2*i + 1];
  }
  T query(int lo, int hi)
  {
    T ans = nil;
    for (lo += size, hi += size + 1; lo < hi; lo >>= 1, hi >>= 1)
    {
      if (lo & 1) ans = ans + st[lo++];
      if (hi & 1) ans = ans + st[--hi];
    }
    return ans;
  }
  void update(int pos, T value)
  {
    st[pos + size] = data[pos] = value;
    for (int i = (pos + size) >> 1; i; i >>= 1)
      st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

int main()
{
  int n; scanf("%d", &n);
  segtree = Segtree<Data>(n, nil);
  for (int i = 0; i < n; i ++) scanf("%d", &segtree.data[i].value);
  segtree.build();

  char kind[2];
  while (scanf(" %s", kind) != EOF)
  {
    if (kind[0] == 'Q')
    {
      int lo, hi; scanf("%d %d", &lo, &hi);
      printf("Sum(%d, %d) = %d\n", lo, hi, segtree.query(lo, hi).value);
    }
    else if (kind[0] == 'U')
    {
      int pos, value; scanf("%d %d", &pos, &value);
      segtree.update(pos, Data{value});
      printf("Update(%d with %d)\n", pos, value);
    }
  }
  return 0;
}