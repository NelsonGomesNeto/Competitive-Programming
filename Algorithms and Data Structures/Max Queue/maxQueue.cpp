#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

template<class T>
struct MinMaxQueue
{
  deque<T> maxdq, mindq; queue <T> q;
  void clear()
  {
    maxdq.clear(), mindq.clear();
    while (!q.empty()) q.pop();
  }
  void push(T x)
  {
    while (!maxdq.empty() && x > maxdq.back())
      maxdq.pop_back();
    while (!mindq.empty() && x < mindq.back())
      mindq.pop_back();
    q.push(x), maxdq.push_back(x), mindq.push_back(x);
  }
  T max() { assert(!maxdq.empty()); return maxdq.front(); }
  T min() { assert(!mindq.empty()); return mindq.front(); }
  T front() { assert(!q.empty()); return q.front(); }
  void pop()
  {
    if (q.empty())
      return;
    if (q.front() == maxdq.front())
      maxdq.pop_front();
    if (q.front() == mindq.front())
      mindq.pop_front();
    q.pop();
  }
  size_t size() { return q.size(); }
  bool empty() { return q.empty(); }
};
MinMaxQueue<lli> mmq;

int main()
{
  int q;
  while (scanf("%d", &q) != EOF)
  {
    mmq.clear();
    while (q--)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        lli x; scanf("%lld", &x);
        mmq.push(x);
      }
      else if (op == 2) printf("front: %lld, max: %lld, min: %lld\n", mmq.front(), mmq.max(), mmq.min());
      else mmq.pop();
    }
  }
  return 0;
}