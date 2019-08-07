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
  * [HackerEarth Problem Package](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/maximum-flow/practice-problems/)
  * [UVA Problem Package](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=685)

## Min Cost Flow :star:
* #### minCostFlow with successive shortest paths.
  * ##### Shortest path algorithms (ordered by the fastest first):
    Always use *Dijkstra with Potentials*, unless the graph has negative edges at the first step; in these cases, use *SPFA*
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

# Segment Tree :star:
## Segment Tree without Lazy Propagation :star:
* #### Problems
  * [Fundraising](https://www.urionlinejudge.com.br/judge/en/problems/view/2700) (It's not trivial, we use a max segtree to apply a greedy strategy)
  * [Keep It Energized](https://www.urionlinejudge.com.br/judge/en/problems/view/2010) (It's not trivial, we use min segtree to apply a greedy strategy)
  * [Marathon](http://www.usaco.org/index.php?page=viewproblem2&cpid=495) (MIND BLOWING, store: full, cutLeft, cutMid, cutRight, lo, hi; and merge stuff)
  * [Kaori, Asuna e Kirito](https://thehuxley.com/problem/1857) (AMAZING, segment tree's node is a array 32 ints)
  * [Culture Code](https://codeforces.com/contest/1197/problem/E) (Interesting use of segment tree to apply a greedy strategy)

## Segment Tree with Lazy Propagation :star:
* #### Problems
  * [Light Switching](https://www.spoj.com/problems/LITE/) (Pure Segment Tree)
  * [11402 - Ahoy Pirates](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397) (Set update, be careful)
  * [Acordes Intergaláticos](https://www.urionlinejudge.com.br/judge/en/problems/view/2658) (Time is very short, be careful with constants)
  * [Present](https://codeforces.com/contest/460/problem/C) ((Min, Pos) Segtree with Lazy Propagation; implementation is interesting ^~^)

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
  * [10938 - Flea Circus](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1879) (Pretty mind blowing, but very good to practice)
  * [Tourists](https://open.kattis.com/problems/tourists) (Easy and pure LCA problem, it's AMAZING)
  * [Boxes](https://open.kattis.com/problems/boxes) (Amazing LCA on forests (it's the, just run the DFS for each root), I LOVED IT)
  * [Pokegene](https://open.kattis.com/problems/pokegene) (MIND BLOWING Trie + LCA problem, I LOVED IT)
  * [Linhas de Metrô](https://www.urionlinejudge.com.br/judge/en/problems/view/2887) (Clever LCA problem, look for combinations of paths, AMAZING)
  * [Company](https://codeforces.com/contest/1062/problem/E) (MIND BLOWING "in and out" + LCA problem, look for the border vertices)

# Graph
* #### Problems
  * [Shipping](https://thehuxley.com/problem/1997) (Very pure Dijkstra)
  * [Zak Galou](https://www.urionlinejudge.com.br/judge/pt/problems/view/1409) (Coin change DP + Dijkstra)
  * [Galactic Taxes](https://www.urionlinejudge.com.br/judge/pt/problems/view/2011) (Ternary Search + Dijkstra)
  * [796 - Critical Links](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737) (Pure bridge detection)
  * [Series of Tubes](https://www.urionlinejudge.com.br/judge/es/problems/view/2899) (Interesting bridge detection)
  * [Edges contraction](https://thehuxley.com/problem/1050) (Interesting DSU problem)
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
  * [HackerEarth ShortestPath](https://www.hackerearth.com/pt-br/practice/algorithms/graphs/shortest-path-algorithms/practice-problems/?sort_by=solved) (There are some interesting problems ^~^)

# Dynamic Programming (DP)
## Longest Common Sequence (LCS)
* #### Problems:
  * [531 - Compromise](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=472) (Pure, but needs retrieval)

## Longest Incresing Sequence (LIS)
* #### Problems:
  * [Smider Pan](https://www.urionlinejudge.com.br/judge/en/problems/view/2943) (Pure LIS problem, n² is enough, but learn the nlg)

## Coin change
* #### Problems:
  * [357 - Let Me Count The Ways](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=293) (Very pure)
  * [The Values You Can Make](https://codeforces.com/contest/687/problem/C) (Incredible bitmask problem)

## Maximum subarray
* #### Problems
  * [10755 - Garbage Heap](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1696) (Maximum subarray sum, easy to think: O(n^6), mind blowing accSum: O(n^5); both pass very easily though)

## Digit DP
* #### Problems
  * [Enigma](https://www.urionlinejudge.com.br/judge/en/problems/view/2699) (Pure + mod of bigInteger)

## Precalculation
* #### Problems
  * [Little Girl and Maximum Sum](https://codeforces.com/problemset/problem/276/C) (Interesting easy in and out problem)
  * [679 - Dropping Balls](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=620) (Very interesting)
  * [Gargari and Bishops](https://codeforces.com/contest/463/problem/C) (Amazing precalculation problem, think of an 1D way to represent the diagonals)
  * [Go--](https://www.urionlinejudge.com.br/judge/en/problems/view/2241) (Awesome accumulated sum problem, n³ is pretty easy, but try to improve it to n² (the idea is slightly different though))

## Knapsack
* #### Problems
  * [Shovels Shop](https://codeforces.com/contest/1154/problem/F) (Mind blowing knapsack problem)
  * [Beautiful Array](https://codeforces.com/contest/1155/problem/D) (Very beautiful knapsack problem)
  * [Neko and Aki's Prank](https://codeforces.com/contest/1152/problem/D) (Interesting knapsack using parenthesis balancement idea)

## Tree
* #### Problems
  * [Valera and Elections](https://codeforces.com/contest/369/problem/C) (Easy but beautiful DP on Tree)
  * [Distance in Tree](https://codeforces.com/problemset/problem/161/D) (Awesome DP on Tree)
  * [Serval and Rooted Tree](https://codeforces.com/contest/1153/problem/D) (Very interesting use of recursion (no DP actually needed))

## Bitmask
* #### Problems
  * [Moovie Mooving](http://www.usaco.org/index.php?page=viewproblem2&cpid=515) (Amazing bitmask dp problem)
  * [Guard Mark](http://www.usaco.org/index.php?page=viewproblem2&cpid=494) (Mind blowing bitmask dp + greedy problem)

# Search
* #### Problems
  * [12192 - Grapevine](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3344) (Interesting lowerBound + upperBound)
  * [Hamburgers](https://codeforces.com/problemset/problem/371/C) (Interesting easy binary search problem)
  * [Wonder Room](https://codeforces.com/contest/466/problem/B) (Seems very easy, but binary search the area (and use math) is the way)
  * [Multiplication Table](https://codeforces.com/contest/448/problem/D) (Amazing binary search + math)
  * [Increasing by Modulo](https://codeforces.com/contest/1169/problem/C) (Very interesting binary search + math)
  * [Born This Way](https://codeforces.com/contest/1148/problem/B) (Interesting easy binary search problem, I like to use my own lower bound)

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

# Geometry
* #### Problems
  * [Confederation](https://www.urionlinejudge.com.br/judge/en/problems/view/1710) (Dividing space with planes, very nice (map))
  * [Power Transmission](https://codeforces.com/contest/1163/problem/C2) (Amazing lines and intersections problem, use ax + by = c equation)
  * [Rectangle Park](https://www.urionlinejudge.com.br/judge/en/problems/view/1938) (Amazing coordinate compression problem)

# Greedy
* #### Problems
  * [Walking Robot](https://codeforces.com/contest/1154/problem/D) (Interesting greedy problem)
  * [Increasing Subsequence](https://codeforces.com/contest/1157/problem/C2) (No DP, go straight to greedy)
  * [N Problems During K Days](https://codeforces.com/contest/1157/problem/D) (Math + BinarySearch + Greedy)
  * [Minimum Array](https://codeforces.com/contest/1157/problem/E) (Much easier than it seems)
  * [Maximum Balanced Circle](https://codeforces.com/contest/1157/problem/F) (AWESOME, remeber that it's a circle (so it goes back and forth))
  * [Trabalho do Papa](https://neps.academy/problem/343) (Mind blowing greedy sorting to allow amazing DP; DO IT)
  * [Bicoloured RBS](https://codeforces.com/contest/1167/problem/D) (Very interesting parenthesis balancing problem, think simple)



# Data Structures
## Trie
* #### Problems
  * [Good Substrings](https://codeforces.com/contest/271/problem/D) (Amazing Trie problem, memeHorse: ILOVEIT)

## DSU
* #### Problems
  * [0-1-Tree](https://codeforces.com/contest/1156/problem/D) (Amazing DSU + combinatorics problem)
  * [Quantity of String](https://codeforces.com/contest/151/problem/D) (Very interesting use of DSU on palindromes)
  * [Raman's Problem](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/ramans-problem/) (Very nice DSU + combinatorics problem)
  * [Monk missing home](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/monk-missing-home-code-monk/description/) (Needs a very interesting modification on merge function)
  * [City and Campers 2](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/city-and-campers-2/) (Needs a quite hard implementation on DSU's merge; do the first one before)
  * [Classic task](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/classic-task-39656dbf/description/) (MIND BLOWING use of binary lifting idea, it's AMAZING)
  * [HackerEarth DSU Problems](https://www.hackerearth.com/pt-br/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/) (There are some interesting problems)

# Etc
* #### Problems
  * [Balé](http://olimpiada.ic.unicamp.br/pratique/p1/2011/f2/bale/) (Easy inversion count problem)
