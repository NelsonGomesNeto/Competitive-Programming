It's pretty similar to day 5 but iterating through the passwords is a lot more
interesting hahaha.

My immediate idea to "incrementing" the password was to convert the password
into a number and let he math do the rest hahaha.

I didn't implement any optimizations on skip invalids like if there is an `i`:
just pick the next letter for it and start with `a` on all the rest.

Curiously, the `ghijklmn` example is much harder than the actual input
`hxbxwxba`. Likely because it takes MANY iterations to get to that prohibited
`i`.

Anyways, `ghijklmn` took ~3s. Then I optimized the code a bit to do 0
allocations and evalute all rules in a single string pass.
Then, it all runs in 700ms without O2 and 80ms with O2 \o/.

What about `iaaaaaaa`? 60s and 8031810907 iterations hahahaha.
With the optimization to skip the `iol`, it goes down to 6ms without O2!!! \o/

Cool problem \o/.