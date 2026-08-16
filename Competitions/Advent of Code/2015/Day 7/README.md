Emulating the circuit didn't require any optimizations but writing the emualtor
was AWESOME.
I finally played a bit with graphviz, what a nice library.

I didn't understand the circuit yet but the value of `a` seems to be constructed
as follows:
  a = a | (SomeLongComputation() & 1)
  a <<= 1
  a = a | (ContinuationOfComputation() & 1)
In other words, it is building `a` bit by bit with the single bit output of some
computation that is chained up to the last bit of `a`.
Something also seems to be output to `ma`.

Anyways, this made my weekend. 300% worth it.