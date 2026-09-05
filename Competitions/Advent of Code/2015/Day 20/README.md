I immediately thought about the Eratosthenes Sieve hahaha.

But I tried implementing it in O(n^2) first by simply computing the number of
presents on each house. That allowed me to get a sense of the growth: O(n*lg).
So, the answer would likely be within the first 10^7 houses.
In hindsight, each position gets its divisors so it really would be around
O(n*lg) hahaha.

Anyways, I implemented the sieve up to 10^7 and just looped to find the answer.
The sieve is O(n*log(log(n))), so it ran in 300ms for the first part and 100ms
for the second part \o/.