# Flow and Matching :star:
## Max Flow, Maximum Matching :star:
* #### Dinic's algorithm is enough for every problem I've tested. NEVER change the algorithm, there's always a way to model in a way that it will magically work :smiley:
* #### Problems
  * [Fast Flow](https://www.spoj.com/problems/FASTFLOW/) (Heavy optimization needed)
  * [Matching](https://www.spoj.com/problems/MATCHING/) (Heavy optimization needed)
  * [Attacking Rooks](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=602&page=show_problem&problem=4406) (Modeling is pretty incredible)
  * [Martian Volei](https://thehuxley.com/problem/643) (Modeling is beautiful and a bit simple)
  * [670 - The dog task](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=611) (Modeling isn't hard)
  * [Keep It Covered](https://www.urionlinejudge.com.br/judge/pt/problems/view/2705) (Modeling is quite hard... Probably because I wanted to retrieve exact pieces and orientation (for visualization purpose: [keepitcovered.pde](https://github.com/NelsonGomesNeto/ProgramC/tree/master/Visualization/KeepItCovered/keepitcovered)), but here are some hints: bipartite, needs "unification vertex", checkerboard, only dots and lines need to be mapped)
  * [Delivery Bears](https://codeforces.com/contest/653/problem/D) (BinarySearch + MaxFlow)
  * [Soldier And Traveling](https://codeforces.com/contest/546/problem/E) (Easy modeling MaxFlow, needs information recover from flow)
  * [Kill the Werewolf](https://www.urionlinejudge.com.br/judge/en/problems/view/2354) (Modeling isn't trivial, but it's interesting)
  * [Olimpíadas](https://br.spoj.com/problems/OLIMP/) (Modeling is easy, but you will have to find the flow paths; it's amazing)
  * [No Prime Sum](https://csacademy.com/contest/archive/task/no-prime-sum) (Interesting Minimum Vertex Cover problem, split into odd and even numbers to apply MVC)
  * [HackerEarth Problem Package](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/maximum-flow/practice-problems/)
  * [UVA Problem Package](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=685)
  * [Zebraness](https://atcoder.jp/contests/abc193/tasks/abc193_f) (AMAZING MaxFlow problem, though I don't know how to extract the optimal choice, only the value of it :/)

## Min Cost Flow :star:
* #### minCostFlow with successive shortest paths.
  * ##### Shortest path algorithms (ordered by the fastest first):
    Prefer *Dijkstra with Potentials*, unless the graph has negative edges at the first step; in these cases, use *SPFA*. *SPFA* might be faster sometimes.
    * Dijkstra with Potentials O(|E| + |V|log|V|): The intuition behind is that it calculates to difference in cost instead of the actual cost of each step; therefore, it won't have negative costs. It's identical to an ordinary Dijkstra, except that "cost[v] = cost[u] + graph[u][v]", you will have "cost[v] = cost[u] + graph[u][v] + potentials[u] - potentials[v]" and after running dijkstra, you will need to add the costs to the potentials.
    * SPFA O(|V||E|) but usually O(|E|): Kind of a mix between bellmanFord and dijkstra, but doesn't uses a priority queue, so it works perfectly even with negative costs.
    * bellmanFord O(|V||E|): It's very straight forward, but it's dangerous to use it here, although will work mostly.

* #### The successive shortest paths implementation is easy to implement and understand, so I'm using it. It seems like it's more then enough for everything.
* #### Problems
  * [10594 - Data Flow](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1535) (It requires bidirectional edges, so be careful)
  * [11301 - Great Wall of China](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=808&problem=2276) (Requires better shortest path algorithm then bellmanFord's, SPFA will do; and has cost on vertices)
  * [10806 - Dijsktra, Dijsktra](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=808&page=show_problem&problem=1747) (Edges must me utilized only once, so modeling is a bit mind blowing, but quite easy)
  * [Beating the dices in their own game](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/minimum-cost-maximum-flow/practice-problems/algorithm/beating-the-dices-in-their-own-game/) (Matrix won't do, use list of edges)
  * [Amazing Race](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/minimum-cost-maximum-flow/practice-problems/algorithm/amazing-race-3/)
  * [Ciel and Duel](https://codeforces.com/contest/321/problem/B) (*maxCostFlow* haha, an additional if is needed though)
  * [Almost Permutation](https://codeforces.com/problemset/problem/863/F) (Multiple connections between two vertices: interesting math trick)
  * [UVA Problem Package](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=808)
  * [Armchairs](https://codeforces.com/contest/1525/problem/D) (Very interesting MinCostFlow problem, minimize the amount of edges and boyah)

# Segment Tree :star:
## Segment Tree without Lazy Propagation :star:
* #### Problems
  * [Fundraising](https://www.urionlinejudge.com.br/judge/en/problems/view/2700) (It's not trivial, we use a max segtree to apply a greedy strategy)
  * [Keep It Energized](https://www.urionlinejudge.com.br/judge/en/problems/view/2010) (It's not trivial, we use min segtree to apply a greedy strategy)
  * [Marathon](http://www.usaco.org/index.php?page=viewproblem2&cpid=495) (MIND BLOWING, store: full, cutLeft, cutMid, cutRight, lo, hi; and merge stuff)
  * [Kaori, Asuna e Kirito](https://thehuxley.com/problem/1857) (AMAZING, segment tree's node is a array 32 ints)
  * [Culture Code](https://codeforces.com/contest/1197/problem/E) (Interesting use of segment tree to apply a greedy strategy)
  * [Enemy is weak](https://codeforces.com/problemset/problem/61/E) (MIND BLOWING inversion count problem)

## Segment Tree with Lazy Propagation :star:
* #### Problems
  * [Light Switching](https://www.spoj.com/problems/LITE/) (Pure Segment Tree)
  * [11402 - Ahoy Pirates](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397) (Set update, be careful)
  * [Acordes Intergaláticos](https://www.urionlinejudge.com.br/judge/en/problems/view/2658) (Time is very short, be careful with constants)
  * [Present](https://codeforces.com/contest/460/problem/C) ((Min, Pos) Segtree with Lazy Propagation; implementation is interesting ^~^)
  * [Fixed Point Removal](https://codeforces.com/contest/1405/problem/E) (Awesome Lazy Segtree problem. Offline solution ftw (although I don't like it))

## Persistent Segment Tree :star:
* #### Problems:
  * [Codeforces' list of problems](https://codeforces.com/blog/entry/56880) (Many nice problems)
  * [Make Versions in Segment Tree](https://www.spoj.com/problems/PSEGTREE/) (Pure straight Persistent Segment Tree)
  * [K-th Number](https://www.spoj.com/problems/MKTHNUM/) (K-th number on sorted range, basic application of Persistent Segment Tree)
  * [K-Query Online](https://www.spoj.com/problems/KQUERYO/) (# of elements greater than k in range, basic application of Persistent Segment Tree)
  * [Cut and Stick](https://codeforces.com/contest/1514/problem/D) (Awesome use of Persistent Segment Tree, actually there are MANY ways to solve this problem)

# Lowest Common Ancestor (LCA) :star:
* There are two main implementations of LCA, both use a Sparse Table to speed up their queries and takes O(n\*lg) to preprocess.
* Eulerian Tour (O(1) queries):
  * Despite being extremely fast and very easy to understand, it's not flexible
  * It works by building a RMQ on top of the tree's Eulerian tour
    * Run a DFS, *every time* you're in u: add u to the Eulerian tour
      * Even each single time you return from it's child
    * Build RMQ on top of the Eulerian Tour
      * LCA == min RMQ query(from min(first[u], first[v]) to max(first[u], first[v]))
* Binary Lifting (O(lg) queries): [Tutorial](https://codeforces.com/blog/entry/22325)
  * Probably more then enough for every problem, and it's very flexible. You can
  answer not only LCA queries, but also all sort of query that involves the path
  (and even weight) between two nodes.
  * It uses DP, where: ancestor(u, i) is the 2^i ancestor of u
    * ancestor(u, 0) = parent of u (you run a DFS to fill up these, also store the level of each node)
    * ancestor(u, i) = ancestor(ancestor(u, i - 1), i - 1)
      * It's saying that the 2^i ancestor is the 2^(i - 1) ancestor of the 2^(i - 1) ancestor
      * Think this way: what is in the middle between u and it's 2^i ancestor?
      Yes, the 2^(i - 1) ancestor, which it self has a 2^(i - 1) ancestor; and
      it's exactly the 2^i ancestor of u. Why this? Because we can bottom up fill it easily.
      We already have the 2^0 ancestor, therefore, we can fill the 2^1, then 2^2, ...
    * To answer the query, we first will need u and v to be at the same level, so
    we go up with the lowest until the levels are the same. Now, we can climb up until
    the ancestor of them are equal. It's quite tricky to grasp everything that is going
    on, but I will so do a video about it (*TODO*).
* #### Problems
  * [Lowest Common Ancestor](https://www.spoj.com/problems/LCA/) (Pure LCA, no tricks; but test cases are very weak)
  * [Match Match](http://www.codcad.com/problem/147) (Pure LCA, but queries for distance)
  * [Ants Colony](http://www.codcad.com/problem/160) (Same as above, but edges have distance)
  * [Lowest Common Ancestor](https://www.codechef.com/problems/TALCA) (Clever, but only uses standard and pure LCA)
  * [Imperial Roads](https://www.urionlinejudge.com.br/judge/en/problems/view/2703) (Binary Lifting to query heaviest edge from u and v to the LCA)
  * [Blood Cousins](https://codeforces.com/contest/208/problem/E) (Amazingly clever, needs kthAncestor (easy) and "in and out" idea)
  * [Fools and Roads](https://codeforces.com/contest/191/problem/C) (Mind blowing: After a bunch of queries, print how many times each edge was used; "in and out" idea)
  * [A and B and Lecture Rooms](https://codeforces.com/contest/519/problem/E) (Interesting: dp count nodes reachable from u and binary lift to answer queries; NICE)
  * [Duff in the Army](https://codeforces.com/contest/587/problem/C) (Mind blowing binary lifting to slit people)
  * [Greedy Merchants](https://codeforces.com/contest/178/problem/B3) (Bridge + LCA, it's marvelous ^~^)
  * [Archeology](https://codeforces.com/contest/176/problem/E) (Insert and remove from subtree, queries sum of edges; it's BRILLIANT, there's a tutorial in my code)
  * [Information Graph](https://codeforces.com/contest/466/problem/E) (Mind fireworks: Offline queries + Union Find + (LCA or in out DP))
  * [Kth Ancestor](https://www.hackerrank.com/challenges/kth-ancestor/problem) (Easy pure but very interesting ^~^)
  * [10938 - Flea Circus](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1879) (Pretty mind blowing and very good to practice)
  * [Tourists](https://open.kattis.com/problems/tourists) (Easy and pure LCA problem, it's AMAZING)
  * [Boxes](https://open.kattis.com/problems/boxes) (Amazing LCA on forests (it's the, just run the DFS for each root), I LOVED IT)
  * [Pokegene](https://open.kattis.com/problems/pokegene) (MIND BLOWING Trie + LCA problem, I LOVED IT)
  * [Linhas de Metrô](https://www.urionlinejudge.com.br/judge/en/problems/view/2887) (Clever LCA problem, look for combinations of paths, AMAZING)
  * [Company](https://codeforces.com/contest/1062/problem/E) (MIND BLOWING "in and out" + LCA problem, look for the border vertices)
  * [QTREE2](https://www.spoj.com/problems/QTREE2/) (This problem is a MUST DO with Binary Lifting, at most O(lg(n)) in both queries, you can do it)
  * [Heavy Buckets](https://atcoder.jp/contests/abc438/tasks/abc438_e) (Forget about LCA, this is PURE Binary Lifting! And you don't even need to build trees or care about cycles!)

# Heavy-Light Decomposition (HLD)
* #### Problems
  * [QTREE](https://www.spoj.com/problems/QTREE/) (First problem if you want to learn HLD)
  * [QTREE3](https://www.spoj.com/OI/problems/QTREE3/) (You will have to submit somewhere else, but try it, it's a different mindblowing way to use HLD)
  * [Árvore Colorida](https://neps.academy/problem/777) (Very interesting HLD problem, bitmask ftw)
  * [Water Tree](https://codeforces.com/contest/343/problem/D) (MIND BLOWING HLD problem, you can do without subtree query and update; but to learn that is marvelous)
  * [Pairs of Paths](https://codeforces.com/contest/1486/problem/F) (AWESOME HLD problem, it's possible to do without HLD, but it's interesting to use HLD with values on edges)

# Graph
## Shortest Path, MST, Traversal, Topological Sort, ...
* #### Problems
  * [Shipping](https://thehuxley.com/problem/1997) (Very pure Dijkstra)
  * [Zak Galou](https://www.urionlinejudge.com.br/judge/pt/problems/view/1409) (Coin change DP + Dijkstra)
  * [Galactic Taxes](https://www.urionlinejudge.com.br/judge/pt/problems/view/2011) (Ternary Search + Dijkstra)
  * [796 - Critical Links](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737) (Pure bridge detection)
  * [Series of Tubes](https://www.urionlinejudge.com.br/judge/es/problems/view/2899) (Interesting bridge detection)
  * [Dima and Bacteria](https://codeforces.com/contest/400/problem/D) (Very interesting bfs/dsu + FloydWarshall problem)
  * [Rota Crítica](https://br.spoj.com/problems/ROTA/) (Ad-hoc dfs problem)
  * [Lonely Island](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/topological-sort/practice-problems/algorithm/lonelyisland-49054110/description/) (Very interesting topological sort problem)
  * [Highway Decommission](https://www.urionlinejudge.com.br/judge/en/problems/view/2910) (Very interesting Dijkstra problem)
  * [Anton and Tree](https://codeforces.com/contest/734/problem/E) (Very interesting DFS + tree diameter problem)
  * [Checkposts](https://codeforces.com/problemset/problem/427/C) (Amazing Strongly Connected Components problem)
  * [Misha and Forest](https://codeforces.com/contest/504/problem/A) (Surprising Topological Sort problem)
  * [Sleepy Game](https://codeforces.com/contest/936/problem/B) (Very interesting DFS problem + path construction)
  * [Teletransport](https://www.urionlinejudge.com.br/judge/en/problems/view/1713) (Exponentiate graph to count all possible paths from u to v)
  * [Miss Worm](https://www.urionlinejudge.com.br/judge/en/problems/view/1711) (Very interesting cycle finding + dijkstra problem)
  * [Neko and Flashback](https://codeforces.com/contest/1152/problem/E) (Awesome eulerian path problem)
  * [Street Deviation](https://www.urionlinejudge.com.br/judge/en/problems/view/1442) (Interesting tarjan (bridges) + kosaraju (stronglyConnectedComponents) + dfs problem)
  * [The perfect XOR](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/articulation-points-and-bridges/practice-problems/algorithm/question-5-34/) (Very interesting tarjan (articulation points) problem)
  * [Optical Fiber](https://www.urionlinejudge.com.br/judge/en/problems/view/2941) (Interesting MST problem)
  * [Mania de Par](https://www.urionlinejudge.com.br/judge/en/problems/view/1931) (Remember, Dijkstra is a DP algorithm)
  * [Distruibição de Camisas](https://thehuxley.com/problem/676) (Very interesting Floyd-Warshall + all permutations problems; can also be done with all bitmasks + MST (BEAUTIFUL))
  * [Greg and Graph](https://codeforces.com/contest/295/problem/B) (MIND BLOWING Floyd-Warhsall problem, adding vertices while running Floyd, same complexity)
  * [Missile Silos](https://codeforces.com/problemset/problem/144/D) (Very interesting Dijkstra problem, remember that missiles are place only at the shortest distant positions)
  * [Book of Evil](https://codeforces.com/contest/337/problem/D) (Awesome bfs problem, find diameter and run BFS on vertices from diameter path)
  * [Tree Paths on a Tree](https://codeforces.com/contest/1294/problem/F) (AMAZING bfs problem, find diameter and store the vertices on it's path to something ;3)
  * [Nearest Opposite Parity](https://codeforces.com/contest/1272/problem/E) (Surprising BFS + DP problem, NICE)
  * [HackerEarth ShortestPath](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/shortest-path-algorithms/practice-problems/?sort_by=solved) (There are some interesting problems ^~^)
  * [Egor in the Republic of Dagestan](https://codeforces.com/contest/1407/problem/E) (Longest shortest path?? hehe; Awesome constructive algorithm using BFS)
  * [Graph and Queries](https://codeforces.com/contest/1417/problem/F) (Mind blowing DSU + EulerTour + Segtree problem)
  * [Avoid Rainbow Cycles](https://codeforces.com/contest/1408/problem/E) (Awesome use of MST; hint: bipartite graphs)
  * [Jaime's greedy delivery](https://codeforces.com/gym/102890/problem/J) (Awesome multiple BFSs + DP)
  * [Fib-tree](https://codeforces.com/contest/1491/problem/E) (NICE simple traversal problem)
  * [Paired Payment](https://codeforces.com/contest/1486/problem/E) (NICE Dijkstra with states problem)

## Centroid Decomposition
* #### Problems
  * [Ciel the Commander](https://codeforces.com/problemset/problem/321/C) (Pure Centroid Decomposition)
  * [Xenia and Tree](https://codeforces.com/contest/342/problem/E) (Mind blowing Centroid Decomposition + LCA problem)
  * [Query on a Tree IV](https://www.spoj.com/problems/QTREE4/) (Very similar to Query on a Tree V, but even harder; mind blowing but strongly recommended)
  * [Query on a tree V](https://www.spoj.com/problems/QTREE5/) (Same as Xenia and Tree, but with harder update)

# Dynamic Programming (DP)
## Longest Common Sequence (LCS)
* #### Problems:
  * [531 - Compromise](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=472) (Pure, but needs retrieval)
  * [Greenhouse Effect](https://codeforces.com/contest/269/problem/B) (Very interesting unexpected LCS)

## Longest Incresing Sequence (LIS)
* #### Problems:
  * [Smider Pan](https://www.urionlinejudge.com.br/judge/en/problems/view/2943) (Pure LIS problem, n² is enough, but learn the nlg)
  * [Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) (MIND BLOWING LIS, reduce the n² DP version to n*lg)

## Coin change
* #### Problems:
  * [357 - Let Me Count The Ways](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=293) (Very pure)
  * [The Values You Can Make](https://codeforces.com/contest/687/problem/C) (Incredible bitmask problem)
  * [Crested Ibis vs Monster](https://atcoder.jp/contests/abc153/tasks/abc153_e) (Awesome, Bottom-Up ftw, cheapest way to hit H)

## Maximum subarray
* #### Problems
  * [10755 - Garbage Heap](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1696) (Maximum subarray sum, easy to think: O(n^6), mind blowing accSum: O(n^5); both pass very easily though)

## Digit-DP
* #### Problems
  * [Enigma](https://www.urionlinejudge.com.br/judge/en/problems/view/2699) (Pure + mod of bigInteger)
  * [Daniel and Spring Cleaning](https://codeforces.com/contest/1245/problem/F) (Very interesting digit-DP using binary representation)
  * [Almost Everywhere Zero](https://atcoder.jp/contests/abc154/tasks/abc154_e) (Nice, couting valids below a limit)
  * [Digits Count](https://www.urionlinejudge.com.br/judge/en/problems/view/1138) (NICE digit-DP problem)
  * [Coincidence](https://atcoder.jp/contests/abc138/tasks/abc138_f) (MIND BLOWING, XOR/mod part is a bit hard, but the DigitDP part is worth it)
  * [Digits Paradise in Hexadecimal](https://atcoder.jp/contests/abc194/tasks/abc194_f) (NICE NICE NICE, trust the simple DigitDP)

## Precalculation
* #### Problems
  * [Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) (Interesting easy in and out problem)
  * [679 - Dropping Balls](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=620) (Very interesting)
  * [Gargari and Bishops](https://codeforces.com/contest/463/problem/C) (Amazing precalculation problem, think of an 1D way to represent the diagonals)
  * [Go--](https://www.urionlinejudge.com.br/judge/en/problems/view/2241) (Awesome accumulated sum problem, n³ is pretty easy, but try to improve it to n² (the idea is slightly different though))
  * [Greg and Array](https://codeforces.com/contest/295/problem/A) (AWESOME accumulated sum problem and in-out problem)
  * [Counting Rectangles is Fun](https://codeforces.com/problemset/problem/372/B) (MIND BLOWING accumulated sum problem, 4D WOW, I recommed to optimize to O(n²m² + q))
  * [Interesting Array](https://codeforces.com/contest/482/problem/B) (Nice in-out problem, in-out to build the array and segtree to verify)
  * [Wi-Fi](https://codeforces.com/contest/1216/problem/F) (Awesome bottom-up problem, precalculate the nearest router on the right and choose)
  * [Tanya and Candies](https://codeforces.com/contest/1118/problem/B) (Easy interesting accumulated sum problem)
  * [The Brand New Function](https://codeforces.com/contest/243/problem/A) ("accumulated max position", quite interesting)
  * [Sweets Eating](https://codeforces.com/contest/1253/problem/C) (Very interesting grouping and accumulated sum)
  * [Mike and Feet](https://codeforces.com/contest/547/problem/B) (Amazing subproblem: max(j), where a(j) > a(i) and j < i; can be done with stack or dp; NICE)
  * [Count Good Substrings](https://codeforces.com/contest/451/problem/D) (Very interesting accumulated sum, be cautious with parity)
  * [Arson In Berland Forest](https://codeforces.com/contest/1262/problem/E) (AMAZING Binary Search + accumulated sum, WOW)
  * [Dividing Chocolate](https://atcoder.jp/contests/abc159/tasks/abc159_e) (Interesting easy matrix sum + bitmask + greedy)
  * [Three Blocks Palindrome](https://codeforces.com/contest/1335/problem/E2) (Awesome left and right precalculation; NICE)
  * [Discrete Centrifugal Jumps](https://codeforces.com/contest/1407/problem/D) (Stack trick to precalculate the jumps; NICE (there's also a very simple DP after tehe))
  * [Searchlights](https://codeforces.com/contest/1408/problem/D) (Very accumulated maximum, focus on rx <= sx and ry <= sy hehe)
  * [Altas Aventuras](https://thehuxley.com/problem/190) (Incredibly tricky precomputation. You MUST experiment with the problem BEFORE trying to solve it because we need to reframe the problem to see the precomputation.)

## Knapsack
* #### Problems
  * [Shovels Shop](https://codeforces.com/contest/1154/problem/F) (Mind blowing knapsack problem)
  * [Beautiful Array](https://codeforces.com/contest/1155/problem/D) (Very beautiful knapsack problem)
  * [Neko and Aki's Prank](https://codeforces.com/contest/1152/problem/D) (Interesting knapsack using parenthesis balancement idea)
  * [Dima and Hares](https://codeforces.com/contest/358/problem/D) (Interesting knapsack where information is needed in the next steps)
  * [Yet Another Division Into Teams](https://codeforces.com/contest/1256/problem/E) (Very interesting problem, notice that teams may have size 3, 4 or 5 only)
  * [Large Knapsack](https://www.spoj.com/problems/LKS/) (Interesting Knapsack optimization for big budget)
  * [Two Bracket Sequences](https://codeforces.com/contest/1272/problem/F) (Interesting string dp very similar to knapsack ^~^)
  * [Knapsack for All Segments](https://atcoder.jp/contests/abc159/tasks/abc159_f) (Amazing easy knapsack "with states", NICE)

## Tree DP
* #### Problems
  * [Valera and Elections](https://codeforces.com/contest/369/problem/C) (Easy but beautiful DP on Tree)
  * [Distance in Tree](https://codeforces.com/problemset/problem/161/D) (Awesome DP on Tree)
  * [Serval and Rooted Tree](https://codeforces.com/contest/1153/problem/D) (Very interesting use of recursion (no DP actually needed))
  * [Paint the Tree](https://codeforces.com/contest/1241/problem/E) (NICE DP on Tree, sorting needed to choose the k best choices)
  * [Appleman and Tree](https://codeforces.com/problemset/problem/461/B) (Amazing DP on Tree, also count the number of *valid* ways with 0 black vertices and use that to count the number of ways with 1 black vertices)
  * [Distributing Integers](https://atcoder.jp/contests/abc160/tasks/abc160_f) (Mind blowing combinatorics and DP on Tree with AWESOME re-rooting)
  * [Christmas Game](https://codeforces.com/contest/1498/problem/F) (NICE NICE NICE Nim Game + Tree DP)

## Bitmask
* #### Problems
  * [Moovie Mooving](http://www.usaco.org/index.php?page=viewproblem2&cpid=515) (Amazing bitmask dp problem)
  * [Guard Mark](http://www.usaco.org/index.php?page=viewproblem2&cpid=494) (Mind blowing bitmask dp + greedy problem)
  * [Yet Another Substring Reverse](https://codeforces.com/contest/1234/problem/F) (AWESOME bitmask dp)
  * [Tree and Constraints](https://atcoder.jp/contests/abc152/tasks/abc152_f) (AWESOME bitmask dp)
  * [Minimax Problem](https://codeforces.com/contest/1288/problem/D) (Mind blowing binary search + bitmask dp problem)
  * [Coprime Present](https://atcoder.jp/contests/abc195/tasks/abc195_f) (NICE, gcd(x, y) = gcd(x - y, y) if x > y, beautiful bitmask DP problem)

## Expected Value
* #### Problems
  * [Fork in the Road](https://atcoder.jp/contests/abc144/tasks/abc144_f) (Awesome Expected Value problem, dp on the expected value then test for each vertex (removing a sigle edge))
  * [Hyakugoku and Ladders](https://codeforces.com/contest/1245/problem/E) (AMAZING expected value problem, moving until the end is straightforward and you can emulate the end)
  * [Beautiful Mirros](https://codeforces.com/contest/1265/problem/E) (Mind blowing, you also need to use modular arithmetic to calculate the value, build the equation system and reduce it to a single equation; BEAUTIFUL)

## Just DP ㄟ(≧◇≦)ㄏ
* #### Problems
  * [Fabricating Sculptures](https://matcomgrader.com/problem/9639/fabricating-sculptures/) (Very interesting way of thinking)
  * [Tournament](https://codeforces.com/contest/1260/problem/E) (Amazing dp)
  * [Dr. Evil Underscores](https://codeforces.com/contest/1285/problem/D) (Mind blowing dp with binary search)
  * [Two Arrays](https://codeforces.com/contest/1288/problem/C) (Amazing dp, optimize memo size, N x M memo is possible and beautiful)
  * [Removing Robots](https://atcoder.jp/contests/abc158/tasks/abc158_f) (Mind blowing bottom-up DP, will need accumulated sum and segtree to precalculate some stuff :3)

## Partition DP
* #### Problems
  * [Clear the String](https://codeforces.com/contest/1132/problem/F) (Interesting Partition DP)

## Lagrangian Relaxation (Aliens Trick)
On problem where you need to make up to `k` choices, the immediate DP is often
O(n*k) (position, current_choices). With Lagrangian Relaxation, you can reduce
that to O(n*lg(k)).
### Intuition:
Let `f(x)` be the optimal answer for `x` choices. Let `L(y) = v(y) - y*c(y)`,
where `L(y)` is the optimal answer if every choice has penalty `y` and `v(y)` is
the sum for that penalty. So, you can binary search for the **smallest** penalty
such that `c(y) >= k`. Finally, `ans = L(y) + y*c(y)` (we simply remove the
penalty). Note that this works even if `c(y)` is greater than `k` because the
optimal answer for `k` is in the same line as `c(y)` (slope `y`), so removing
the penalty will fix the answer automatically \o/.

This **only** works if `f(x)` is **concave or convex** and is the reason why the
slope part works. Please consider reading the full proof at
https://usaco.guide/adv/lagrange?lang=cpp.

* #### Problems
  * [Feast](https://oj.uz/problem/view/NOI19_feast) (Very direct aplication of Lagrangian Relaxation)
  * [New Year and Handle Change](https://codeforces.com/contest/1279/problem/F) (Direct application, but needs bottom-up)

## Advanced Optimizations
* #### Problems
  * [Ciel and Gondolas](https://codeforces.com/contest/321/problem/E) (Very interesting Divide and Conquer DP optimization (USE FAST IO, read as char and convert to int))
  * [Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/problem) (Very interesting easy case of Divide and Conquer DP optimization)
  * [Branch Assignment](https://icpc.kattis.com/problems/branch) (AMAZING Divide and Conquer DP optimization)
  * [Lannister Army](https://www.spoj.com/problems/LARMY/) (Interesting Divide and Conquer DP optimization (time limit is very strict, precalculate the getCost))
  * [Make Them Similar](https://codeforces.com/contest/1257/problem/F) (Very interesting Meet In The Middle problem, also need to normalize)
  * [Charlie New PC](https://csacademy.com/ieeextreme-practice/task/charlie-new-pc/) (Amazing Meet In The Middle problem)
  * [Frog 3](https://atcoder.jp/contests/dp/tasks/dp_z) (BEAUTIFUL Convex Hull Trick)
  * [Pictures with Kittens (hard version)](https://codeforces.com/contest/1077/problem/F2) (AMAZING Max Queue, do O(n\*x\*k) and remove k with Max Queue; it might be useful to reduce with SegTree first, but it won't pass)
  * [Square-free division(hard version)](https://codeforces.com/contest/1497/problem/E2) (MIND BLOWING, greedy precalc to maximize something and then traverse with DP using that precalc, BEAUTIFUL)
  * [Skyline Photo](https://codeforces.com/contest/1484/problem/E) (BEAUTIFUL, DP + (SegmentTree or Stacks), LOVELY)
  * [Phoenix and Computers](https://codeforces.com/contest/1515/problem/E) (MIND BLOWING, n^2, try to view on computers as segments)

# Search
* #### Problems
  * [12192 - Grapevine](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3344) (Interesting lowerBound + upperBound)
  * [Hamburgers](https://codeforces.com/problemset/problem/371/C) (Interesting easy binary search problem)
  * [Wonder Room](https://codeforces.com/contest/466/problem/B) (Seems very easy, but binary search the area (and use math) is the way)
  * [Multiplication Table](https://codeforces.com/contest/448/problem/D) (Amazing binary search + math)
  * [Increasing by Modulo](https://codeforces.com/contest/1169/problem/C) (Very interesting binary search + math)
  * [Born This Way](https://codeforces.com/contest/1148/problem/B) (Interesting easy binary search problem, I like to use my own lower bound)
  * [Save the Nature](https://codeforces.com/contest/1241/problem/C) (Awesome binary search for guessing the answer and greedy testing)
  * [Minimizing Difference](https://codeforces.com/contest/1244/problem/E) (AWESOME ternary search inside binary search)
  * [Gluttony](https://atcoder.jp/contests/abc144/tasks/abc144_e) (Interesting easy binary search + greedy problem)
  * [11195 - Another N-Queen problem](https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2136) (Interesting backtracking + bitmasking problem)

# Math
* #### Problems
  * [Jumping Frog](https://www.urionlinejudge.com.br/judge/pt/problems/view/2704) (GCD, it's a very brilliant problem)
  * [Minimum Possible LCM](https://codeforces.com/contest/1154/problem/G) (LCM, very puzzling problem but interesting)
  * [Problem for Nazar](https://codeforces.com/contest/1151/problem/C) (Loads of modular stuff + arithmetic progression)
  * [Number of Components](https://codeforces.com/contest/1151/problem/E) (Contribution to Sum technique)
  * [Valid Sets](https://codeforces.com/contest/486/problem/D) (Beautiful use of produtory and dfs)
  * [Neko does Maths](https://codeforces.com/contest/1152/problem/C) (LCM + GCD, you have to understand both (open their formulas))
  * [Save Energy!](https://codeforces.com/contest/936/problem/A) (Amazing pure math problem (finding the cycle and jumping by it works, but math is way prettier))
  * [Chladni Figure](https://codeforces.com/contest/1162/problem/D) (Interesting math problem (just test with all divisors))
  * [The LCMs Must be Large](https://codeforces.com/contest/1166/problem/E) (Amazing LCM problem, contradiction is the way)
  * [Couples](https://www.urionlinejudge.com.br/judge/en/problems/view/2939) (Interesting combinatorics problem, f(n) * n! * 2^n, the real problem is to find the function f)
  * [Vampires](https://www.urionlinejudge.com.br/judge/en/problems/view/1093) (AWESOME, using Gambler's Ruin is very easy, but try to model as a Markov Chain)
  * [Petya and Divisors](https://codeforces.com/problemset/problem/111/B) (Nice, divisibility problem; don't bother about prime numbers; answer the query and update something ;))
  * [Matrix](https://codeforces.com/contest/364/problem/A) (NICE, try to factor the sum into the multiplication of two parts)
  * [Good Sequences](https://codeforces.com/contest/264/problem/B) (AWESOME, Number Theory + DP problem)
  * [Soldier and Number Game](https://codeforces.com/problemset/problem/546/D) (Requires a *very* optimized primeFactorization, do it while constructing the sieve)
  * [Fedya and Maths](https://codeforces.com/contest/456/problem/B) (Very interesting number theory problem, decompose the exponentials)
  * [Sereja and the Arrangement of Numbers](https://codeforces.com/contest/367/problem/C) (Amazing problem to remind Eulerian Cycle and Eulerian Path)
  * [Knight](https://atcoder.jp/contests/abc145/tasks/abc145_d) (Very interesting problem, a wild unexpected Pascal's Triangle appears)
  * [Flatten](https://atcoder.jp/contests/abc152/tasks/abc152_e) (Amazing modular lcm problem, build lcm using prime factorization)
  * [XOR World](https://atcoder.jp/contests/abc121/tasks/abc121_d) (Amazing, count each bit 1's frequency, from 0 to n is easier :3)
  * [Many Many Paths](https://atcoder.jp/contests/abc154/tasks/abc154_f) (AWESOME, Pascal's Triangle, accumulated sum, choose and summation reduction)
  * [Roaming](https://atcoder.jp/contests/abc156/tasks/abc156_e) (MIND BLOWING, Stars and Bars ftw, empty positions is the way)
  * [Modularness](https://atcoder.jp/contests/abc156/tasks/abc156_f) (AWESOME, modular arithmetic problem; try to solve the opposite of what the problem asks you :3)
  * [Divisible Substring](https://atcoder.jp/contests/abc158/tasks/abc158_e) (NICE, modular arithmetic problem; gcd(p, 10) is very important :3)
  * [Sum of gcd of Tuples (Hard)](https://atcoder.jp/contests/abc162/tasks/abc162_e) (AMAZING use of "dp"/precalculation (while building the answer); try to count how many times each gcd happens)
  * [Three Sequences](https://codeforces.com/contest/1406/problem/D) (NICE, you will get to the idea with paper and pen; think about a rule for b and c, ...)
  * [Oversleeping](https://atcoder.jp/contests/abc193/tasks/abc193_e) (AWESOME, model it as a diophantine equations)
  * [Graph Smoothing](https://atcoder.jp/contests/abc199/tasks/abc199_f) (MIND BLOWING, expected value, matrix exponentiation and graphs)

# Geometry
* #### Problems
  * [Confederation](https://www.urionlinejudge.com.br/judge/en/problems/view/1710) (Dividing space with planes, very nice (map))
  * [Power Transmission](https://codeforces.com/contest/1163/problem/C2) (Amazing lines and intersections problem, use ax + by = c equation)
  * [Rectangle Park](https://www.urionlinejudge.com.br/judge/en/problems/view/1938) (Amazing coordinate compression problem)
  * [Yakininku Optimization Problem](https://atcoder.jp/contests/abc157/tasks/abc157_f) (Very interesting circle intersection problem)
  * [Rain of Fire](https://codeforces.com/contest/1419/problem/F) (Very interesting Geometry + Graph problem, NICE, NICE, NICE)

# Greedy
* #### Problems
  * [Walking Robot](https://codeforces.com/contest/1154/problem/D) (Interesting greedy problem)
  * [Increasing Subsequence](https://codeforces.com/contest/1157/problem/C2) (No DP, go straight to greedy)
  * [N Problems During K Days](https://codeforces.com/contest/1157/problem/D) (Math + BinarySearch + Greedy)
  * [Minimum Array](https://codeforces.com/contest/1157/problem/E) (Much easier than it seems)
  * [Maximum Balanced Circle](https://codeforces.com/contest/1157/problem/F) (AWESOME, remeber that it's a circle (so it goes back and forth))
  * [Trabalho do Papa](https://neps.academy/problem/343) (Mind blowing greedy sorting to allow amazing DP; DO IT)
  * [Bicoloured RBS](https://codeforces.com/contest/1167/problem/D) (Very interesting parenthesis balancing problem, think simple)
  * [Almost Arithmetical Progression](https://codeforces.com/contest/255/problem/C) (Amazing greedy, strongly recommended due to interesting implementation tricks)
  * [Two Contests](https://atcoder.jp/contests/agc040/tasks/agc040_b) (Amazing greedy, minR and maxL may be in the same contest or not, sort ascending and descending by something)
  * [Same Sum Blocks](https://codeforces.com/contest/1141/problem/F2) (Mind blowing, Interval Scheduling problem)

# Data Structures
## Trie
* #### Problems
  * [Good Substrings](https://codeforces.com/contest/271/problem/D) (Amazing Trie problem, memeHorse: ILOVEIT)

## DSU
* #### Problems
  * [0-1-Tree](https://codeforces.com/contest/1156/problem/D) (Amazing DSU + combinatorics problem)
  * [Edges contraction](https://thehuxley.com/problem/1050) (Interesting DSU problem)
  * [Quantity of String](https://codeforces.com/contest/151/problem/D) (Very interesting use of DSU on palindromes)
  * [Raman's Problem](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/ramans-problem/) (Very nice DSU + combinatorics problem)
  * [Monk missing home](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/monk-missing-home-code-monk/description/) (Needs a very interesting modification on merge function)
  * [City and Campers 2](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/city-and-campers-2/) (Needs a quite hard implementation on DSU's merge; do the first one before)
  * [Classic task](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/classic-task-39656dbf/description/) (MIND BLOWING use of binary lifting idea, it's AMAZING)
  * [Harmonious Graph](https://codeforces.com/contest/1253/problem/D) (Remind that DSU can be used to store lot's of interesting informations such as minimum and maximum vertex)
  * [HackerEarth DSU Problems](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/) (There are some interesting problems)
  * [Friend Suggestions](https://atcoder.jp/contests/abc157/tasks/abc157_d) (VERY NICE use of DSU)
  * [Experience](https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C) (Amazingly clever DSU problem, no maps, just a smart use of DSU)

# String
* #### Problems
  * [Pattern Find](https://www.spoj.com/problems/NAJPF/) (Straightforward KMP problem)
  * [Password](https://codeforces.com/contest/126/problem/B) (Interesting prefix function problem)
  * [MUH and Cube Walls](https://codeforces.com/problemset/problem/471/D) (Interesting easy KMP problem)
  * [Gluing Pictures](https://matcomgrader.com/problem/9641/gluing-pictures/) (Awesome Suffix Array problem, beautiful binary search (Suffix Automaton and Suffix Tree may be more direct))
  * [Three Substrigs](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_e) (Awesome string match problem, think about the easy O(n^3) and try to reduce something on it to O(1) (given some precalculations :3))

# Fast Fourier Transform (FFT)
* #### Problems:
  * [Substring 2](https://atcoder.jp/contests/abc196/tasks/abc196_f) (Straightforward String Matching with FFT)
  * [Permutation Concatenation](https://atcoder.jp/contests/abc390/tasks/abc390_g) (Heavy math manipulation to use NTT)

# Interactive
* #### Problems
  * [Chocolate Bunny](https://codeforces.com/contest/1407/problem/C) (Very interesting easy interactive problem)
  * [Deleting Numbers](https://codeforces.com/contest/1406/problem/E) (Nice mathy interactive problem, sqrt ftw)
  * [Median Sort](https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1284) (Awesome interactive sorting problem, InsertionSort + TernarySearch or QuickSort ftw)

# Etc
* #### Problems
  * [Balé](http://olimpiada.ic.unicamp.br/pratique/p1/2011/f2/bale/) (Easy inversion count problem)
  * [Little Elephant and Cards](https://codeforces.com/problemset/problem/204/B) (Interesting easy map problem, can be done using coordinate compression)
  * [Código](https://neps.academy/problem/44) (Intersting set problem)
  * [String Equivalence](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_d) (Awesome normalization problem)
  * [Two Different](https://codeforces.com/contest/1408/problem/F) (Clever constructive problem, aim on two different numbers, please)
