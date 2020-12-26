#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 18; int n;
lli s[1 << maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    int sz = 1 << n;
    for (int i = 0; i < sz; i++)
      scanf("%lld", &s[i]);
    sort(s, s+sz, greater<lli>());

    priority_queue<lli> done;
    done.push(s[0]);
    priority_queue<lli> todo;
    for (int i = 1; i < sz; i++)
      todo.push(s[i]);

    bool ans = true;
    for (int k = 0; k < n && ans; k++)
    {
      int req = 1 << k;
      DEBUG printf("\t%d - %d %d | %d %d\n", sz, k, 1 << k, (int)done.size(), (int)todo.size());
      priority_queue<lli> newDone, newTodo;
      while (!done.empty())
      {
        lli now = done.top();
        newDone.push(now);

        bool had = false;
        while (!todo.empty())
        {
          lli other = todo.top();
          DEBUG printf("\t\t%lld %lld\n", now, other);
          todo.pop();

          if (now > other)
          {
            newDone.push(other);
            had = true;
            break;
          }
          else newTodo.push(other);
        }

        if (had) done.pop();
        else break;
      }
      while (!todo.empty())
      {
        newTodo.push(todo.top());
        todo.pop();
      }

      ans &= done.empty();
      done = newDone, todo = newTodo;
    }
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}