import re
import sys
sys.setrecursionlimit(2**30)

# def solve(expr):
#     expr = ''.join(expr)
#     pluses = expr.split("+")

#     ans = 0
#     for i in pluses:
#         # print("\t", i)
#         minuses = i.split("-")
#         first = True
#         min_ans = 0
#         for j in minuses:
#             # print("\t\t", j, min_ans)
#             mults = map(eval, j.split("*"))
#             mult_ans = 1
#             for k in mults:
#                 mult_ans = mult_ans * k % mod
#             if first:
#                 first = False
#                 min_ans = mult_ans
#             else:
#                 min_ans -= mult_ans
#         ans += min_ans

#     return ans

mod = int(1e9) + 7

t = int(input())

for _ in range(t):
    expr = input()
    chars = set(expr)

    invalid = False
    for c in chars:
        if not c in "0123456789()+-*":
            invalid = True

    double_exp = False
    for a in "+-*":
        for b in "+-*":
            if (a + b) in expr:
                double_exp = True

    invalid_start = not (expr[0] in "0123456789(")
    invalid_end = not (expr[-1] in "0123456789)")

    bad_pairs = re.match(r"(\(\-)|(\(\+)|(\(\*)|(\-\))|(\+\))|(\*\))|([0-9]\()|(\)[0-9])|(\(\))", expr)

    if double_exp or invalid or invalid_start or invalid_end or bad_pairs:
        print("invalid")
    else:
        try:
            res = eval(expr)
            res = (res % mod + mod) % mod
            print(res)
        except:
            print("invalid")