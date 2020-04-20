## Interactive problems:
In these problems, the input is hidden. Your program must make queries to the judge so that, with that info, the program can solve the problem. Of course, the amount of queries you can is limited.

Tutorials:
- [CodeForces](https://codeforces.com/blog/entry/45307)
- [CodeJam](https://codingcompetitions.withgoogle.com/codejam/faq#interactive-problems)

### interactive_judge.py:

  Override the default interaction and you're good to go.
  - read_process will handle a single line input from the program (but you can get more lines b popping more lines from the queue)
  - feed_process will write a string to the program's stdin