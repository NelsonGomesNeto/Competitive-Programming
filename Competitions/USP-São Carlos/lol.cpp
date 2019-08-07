#include <bits/stdc++.h>
using namespace std;

#define DEBUG if(1)
#define MAXN 100
#define MAX INT_MAX
#define MAXLL INT_MAX
#define MAXU ULLONG_MAX
#define MIN -2000000
#define endl "\n"
#define INF INT_MAX
#define MOD 1000000007
#define s(n) scanf("%d", &n)
#define ss(a,b) scanf("%d %d",&a,&b)
#define pb push_back
#define mp make_pair
#define M_PI 3.14159265358979323846
#define sz(a) int(a.size())
#define lli unsigned long long int
#define rep(i,a,n) for (int i=a;i<n;i++)
#define ler(a,n,vec) for(int i=0;i<n;i++)s(a), vec.pb(a)
typedef vector<lli> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
#define DEBUG if(1)
#define F first
#define S second
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ddx[] = {1, 0};
int ddy[] = {1, 1};

int n;
string s;
vi vec[10];
set<int> qt;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;
  cin >> s;

  for(int i=0;i<sz(s);i++){
    vec[s[i] - '0'].pb(i);
    qt.insert(s[i] - '0');
  }

  if(sz(qt) == 1){
    cout << "Yes" << endl;
    return 0;
  }

  for(int i=1;i<sz(s);i++){
    if(s[i] < s[0]){
      cout << "No" << endl;
      return 0;
    }
  }

  vi aux;
  for(int i=0;i<sz(s);i++) if(s[i] == s[0]) aux.pb(i);

  for(int i=0;i<sz(s);i++){
    vi aux2;
    for(int j=0;j<sz(aux);j++){
      int pos = aux[j];
      if(pos == sz(s) - 1){
        if(s[i+1] > s[0]){
          cout << "No" << endl;
          return 0;
        } else if(s[0] == s[i+1]) aux2.pb(0);
      continue;
      }

      if(s[pos+1] < s[i+1]){
        // cout << i+1 << " - " << pos+1 << endl;
        // cout << s[pos+1] << " _ " << s[i+1] << endl;
        cout << "No" << endl;
        return 0;
      } else if(s[pos+1] == s[i+1]) aux2.pb(pos+1);

    }
    // for(auto j : aux) cout << j << " ";
    //   cout << endl;
    aux = aux2;
  }

  cout << "Yes" << endl;

  return 0;
}