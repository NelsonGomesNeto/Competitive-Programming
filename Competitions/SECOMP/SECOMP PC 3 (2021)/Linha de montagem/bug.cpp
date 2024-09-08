#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

typedef long long int lli;
const int limit = 100001;

struct pista {
	lli pista[limit], custo_troca[limit];
	lli entrada, saida;
};

vector< pair<lli, lli> > adjList[limit * 2 + 10];
lli dist[limit * 2 + 10];
pista p[2];
lli N;

lli dijkstra(lli o=0, lli t=N) {
	priority_queue<pair<lli,lli>> pq;
	pq.push({0, o});
	dist[0] = 0;
	while(!pq.empty()) {
		lli u = pq.top().se;
		lli wi = pq.top().fi;
		pq.pop();
		for(auto v : adjList[u]) {
			if(dist[v.se] > dist[u] + v.fi) {
				dist[v.se] = dist[u] + v.fi;
				pq.push({-dist[v.se], v.se});
			}
		}
	}
	return dist[(N *  2) + 1];
}


void solve() {
	cin >> N;
	// adjList.clear();
	// adjList.resize((N * 2) + 2);
	for(lli i = 0; i < (N * 2) + 10; i++) {
		adjList[i].clear();
		dist[i] = LLONG_MAX;
	}

	cin >> p[0].entrada >> p[1].entrada;

	adjList[0].push_back({p[0].entrada, 1});
	adjList[0].push_back({p[1].entrada, N + 1});

	for(lli i = 0; i < N; i++){
		cin >> p[0].pista[i];
		if(i + 1 < N)
			adjList[i + 1].push_back({p[0].pista[i], i + 2});
	}
	for(lli i = 0, j = N + 1; i < N; i++, j++){
		cin >> p[1].pista[i];
		if(i + 1 < N)
			adjList[j].push_back({p[1].pista[i], j + 1});
	}

	for(lli i = 0, j = 1; i < N - 1; i++, j++){
		cin >> p[0].custo_troca[i];
		adjList[(i + 1)].push_back({p[0].pista[i] + p[0].custo_troca[i], 1 + j + N});
	}
	for(lli i = 0, j = N + 1; i < N - 1; i++, j++){
		cin >> p[1].custo_troca[i];
		adjList[j].push_back({p[1].pista[i] + p[1].custo_troca[i], j + 1 - N});
	}
	cin >> p[0].saida >> p[1].saida;

	adjList[N].push_back({p[0].pista[N - 1] + p[0].saida, (2 * N) + 1});
	adjList[N * 2].push_back({p[1].pista[N - 1] + p[1].saida, (2 * N) + 1});

	cout << dijkstra() << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}