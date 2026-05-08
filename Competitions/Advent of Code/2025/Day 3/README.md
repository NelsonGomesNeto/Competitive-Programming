This was interesting and reminded me of https://thehuxley.com/problem/653.

I solved in O(|digits|) per bank by picking the biggest value which would allow me to finish.

That works because the most important thing is to maximize the first digit and the second most important thing is maximize the second digit. So, we simply try to find the biggest first digit possible and follow the same logic for the remaining digits.