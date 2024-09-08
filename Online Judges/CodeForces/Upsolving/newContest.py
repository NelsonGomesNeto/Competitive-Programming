import os

lines = [
    "#include <bits/stdc++.h>",
    "#define DEBUG if(0)\n"
    "#define lli long long int",
    "#define ldouble long double",
    "using namespace std;",
    "",
    "int main()",
    "{",
    "  ",
    "  return 0;",
    "}"
]

folders = os.listdir()
i = 0
for folder in folders:
    if "Contest-" in folder:
        i += 1
contestName = "Contest-%d/" % i
os.mkdir(contestName)

for i in range(ord('A'), ord('F') + 1):
    f = open(contestName + "%c.cpp" % chr(i), "w")
    for line in lines:
        print(line, file=f)
    f.close()
    f = open(contestName + ("%cin" % chr(i)).lower(), "w")
    f.close()