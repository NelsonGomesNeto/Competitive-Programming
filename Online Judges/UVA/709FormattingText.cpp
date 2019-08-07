#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
char s[10000][81];
int sizes[10000], words, length, inf = 1<<20;
int dp[10000][80][2], path[10000][80][2];

int readString(char s[])
{
	char ss; int i = 0;
	scanf("%c", &ss); if (ss == '\n') return(0);
	if (ss == ' ') return(2);
	s[i] = ss;
	while (scanf("%c", &ss) && ss != ' ' && ss != '\n')
		s[++ i] = ss;
	return(1);
}

int readStrings()
{
	int i = 0; memset(s, '\0', sizeof(s));
	while (1)
	{
		int ret = readString(s[i]);
		if (ret == 0) break;
		if (ret == 2) continue;
		sizes[i] = strlen(s[i]);
		i ++;
	}
	return(i);
}

int solve(int i, int now, int one)
{
	if (now > length) return(inf);
	if (i == words) return(now ? (one ? 500 : inf) : 0);

	if (dp[i][now][one] == -1)
	{
		int ans = inf, aux; path[i][now][one] = 0;

		if (!now) ans = solve(i + 1, sizes[i], 1);
		if (one)
		{
			aux = 500 + solve(i + 1, sizes[i], 1);
			if (aux < ans)
			{
				ans = aux;
				path[i][now][one] = -1;
			}
		}
		if (now)
			for (int j = 1; j + now + sizes[i] <= length; j ++)
			{
				aux = (j - 1) * (j - 1) + solve(i + 1, (now + j + sizes[i]) % length, 0);
				if (aux < ans)
				{
					ans = aux;
					path[i][now][one] = j;
				}
			}

		dp[i][now][one] = ans;
	}
	return(dp[i][now][one]);
}

void printSpaces(int amount)
{
	if (amount == -1) { printf("\n"); return; }
	while (amount --) printf(" ");
}

void printSolve()
{
	int now = 0, one = 0;
	for (int i = 0; i < words; i ++)
	{
		// printf("<%d %d %d>\n", now, one, path[i][now][one]);
		if (path[i][now][one]) printSpaces(path[i][now][one]); printf("%s", s[i]);
		if (path[i][now][one] <= 0) now = sizes[i], one = 1;
		else if (path[i][now][one] > 0) { now += path[i][now][one] + sizes[i]; one = 0; }
		if (now == length) printf("\n"), now = 0;
	}
	if (now) printf("\n");
}

int main()
{
	int t = 0;
	while (scanf("%d\n", &length) && length)
	{
		memset(dp, -1, sizeof(dp));
		words = readStrings();
		DEBUG printf("%d\n", words);
		DEBUG for (int j = 0; j < words; j ++)
			printf("%s %d\n", s[j], sizes[j]);

		int cost = solve(0, 0, 0);
		// printf("cost: %d\n", cost);
		printSolve();
		printf("\n");
	}
	return(0);
}