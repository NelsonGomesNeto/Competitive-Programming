#include <bits/stdc++.h>
using namespace std;
 
#define MAXN (int)(1e5 + 5)
#define MAXL 20
#define F first
#define S second
#define endl "\n"
#define MOD (lli)(1e9 + 9)
#define MOD2 (lli)(1e9 + 7)
#define lli long long int
#define sz(a) int(a.size())
#define DEBUG if (0) cout << "aqui" << endl;
#define PI 2 * acos(0.0)
typedef pair<int, lli> ii;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int dddx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dddy[] = {0, 0, 1, -1, 1, -1, 1, -1};

int n;
vector<int> vec;
int ans[MAXN];

priority_queue<ii> pq;
set<int> aux;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  for(int i=0;i<n;i++) {
    int a;
    cin >> a;
    pq.push({a, i});
  }

  int pivo = 0;
  // cout << pq.top() << endl;

  while(!pq.empty()) {
    ii atual = pq.top();
    pq.pop();

    // cout << atual.F << " --- INDEX: " << atual.S << endl;
    // cout << "List: ";
    // for(auto i : aux) cout << i << ' ';
    // cout << endl;

    if(aux.empty()) {
      ans[atual.S] = 0;
      pivo = atual.S;

      // cout << "PIVO: " << pivo << endl;
    } else {
      set<int>::iterator it = aux.lower_bound(atual.S);
      set<int>::iterator it2 = aux.upper_bound(atual.S);
      if(it != aux.begin()) it--;

      if(it2 == aux.end()) {
        it2--;
      }

      // cout << *it << " " << *it2 << endl;

      if(abs(*it2 - atual.S) < abs(*it - atual.S)) {
        ans[atual.S] = ans[*it2] + 1;
      } else if(abs(*it2 - atual.S) > abs(*it - atual.S)) ans[atual.S] = ans[*it] + 1;
      else ans[atual.S] = min(ans[*it], ans[*it2]) + 1;
      // ans[atual.S] = max(ans[*it], ans[*it2]) + 1;

      // if(atual.S < pivo) {
      //   int idxAtual = *aux.lower_bound(atual.S);
      //   cout << "Idx Atual: " << idxAtual << endl;
      //   ans[atual.S] = ans[idxAtual] + 1;
      // } else {
      //   set<int>::iterator it = aux.lower_bound(atual.S);
      //   int idxAtual = 0;
      //   if(it == aux.end()) {
      //     idxAtual = *aux.rbegin();
      //   } else {
      //     it--;
      //     idxAtual = *it;
      //   }
      //   // idxAtual--;
      //   cout << "Idx Atual2: " << idxAtual << endl;
      //   ans[atual.S] = ans[idxAtual] + 1;
      // }
    }
        aux.insert(atual.S);
  }

  for(int i=0;i<n;i++) {
    cout << ans[i] << " ";
  } cout << endl;

  return 0;
}