### First day (code_first_astar_fail.cpp, code_gaussian_elimination.cpp)

Oh wow, this one was AWESOME!

It was the first day of this year that I thought I wasn't going to finish it at
the same day.

I spent A LOT of time trying an A* at the same day. The search space was simply
too big. I eventually optimized too much and ended up getting a wrong answer
because the A* was NOT exploring the shortest path first.

So, I gave up on search and:
1. Modeled the problem as a linear system of equations;
1. Found the free variables with Guassian Elimination;
1. Brute forced all combinations for the free variables.
ABSOLUTE BLISS \o/
It runs in 700ms. Maybe it's possible to optimize further but I stopped for the
day because it was bed time already hahaha.

---

### I couldn't make A* work (code_serious_astar_fail.cpp)

Multiple weeks later, I decided to give A* another try. I tried SO MANY
heuristics and it was VERY fun to explore the problem for multiple days.
Unfortunately, I couldn't find a good heuristic for all the test cases :(.

### DFS with prunes ftw (code_dfs_brute_and_prune.cpp)

I switched to DFS with A LOT of pruning like:
* positive_mask = [val > 0 for val in joltages];
* parity_mask = [val & 1 for val in joltages];
* is this position reachable by parity considering the buttons available?
* order the buttons by considering first the buttons which touch the positions
  with less buttons (ties by BIGGEST joltage);
  * I originaly resolved ties by SMALLEST joltage but it took twice as long to
    run hahaha.
* for each button, discover if that button is the last opportunity to impact a
  position. With this and the above, you can prune very early because you're
  forced to complete positions as early as possible \o/;
* Repeating states was very rare with these prunes, so it was faster to not
  bother pruning repeated states. I just prune by "best answer" so far.

Maybe there are some other smart prunes, but this takes 25s and I'm happy to
have found these prunes \o/.

### DFS bifurcation ftw (code_dfs_bifurcate.cpp, code_dfs_bifurcate_visualization.cpp)

https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory idea is AWESOME!

The core of the idea is the following:
```
for button_press_combination in "all 2^B button presses combinations":
  new_joltages are not all even: skip
  ans = min(ans, presses + 2*Recursively())
```

Hold on, how do you guarantee that the optimal solution can always be divided by
two?

Change the perspective a bit a consider the button presses instead. You can
always order them however you want.
So, you can split the presses in two parts: press each button at most once
(to fix the odds) and then press a sequence of buttons **twice**.

That's really clever. With this idea, I was able to cut it down to 50ms \o/.
Most of the time is spent precomputing something and filling a map so it's
likely possible to make it even faster.