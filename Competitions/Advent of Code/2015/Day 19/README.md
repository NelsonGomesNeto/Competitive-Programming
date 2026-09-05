Oh wow, this one made me worry a lot hahahaha.

I tried going from `e` to the `target` but it exploded SO FAST on a BFS.

Then I swapped to `target` to `e` (in the hopes that the biggest exploration)
happens on a smaller string. But that didn't make it.

So, I added a priority queue to the BFS and the following ordering rule worked:
  Most `steps`, smallest `curr` or lexicographically greater `curr`.
It stills takes 8.5s on O2. So there must be a better way.

I went back and tried that same sorting logic on `e` to `target` but as expected
it doesn't work.

After a lot of hacky optimizations on the constants (not the algorithm it self)
I got it to 6.5s but it was clearly not better. I even tried KMP but that is
worse than just iterating through the string (likely due to caching and AVX
optimizations).

Then, I tried the following ordering rule:
  Smallest `curr` or lexicographically greater `curr`.
For my surprise, it reduced to 7ms!!!!!
In hindsight, maximizing the steps is not good at all because it forces you to
go on some kind of DFS.

What about DFS with that order?
AFAICT, getting to the end is to hard and that order does it so well that the
DFS is equivallent to the A* above.

I can't prove that my order is strong, so I guess I got a bit lucky that the
first solution found was the minimum one.

I played around with bigger inputs and was able to get it to 5K in 1s by
improving the order rule a little bit and limiting the queue size:
  Smallest `curr` or lexicographically greater `curr`, but compare `curr` when
  their size is at most 3 apart.

Really nice problem \o/.