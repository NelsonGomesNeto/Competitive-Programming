import sys
import os

code = sys.argv[1]
test_folder = sys.argv[2]
os.system("g++ %s -o test -std=c++17" % code)

os.system("./test < %s/in > my" % test_folder)
# os.system("python3 agra.py < %s/in > my" % test_folder)

f = open("my", "r")
my = f.readlines()
while my[-1] == "":
    my.pop()
f.close()

f = open("%s/out" % test_folder, "r")
cor = f.readlines()
while cor[-1] == "":
    cor.pop()
f.close()

corrects = sum(m == c for m, c in zip(my, cor))
print(corrects, len(my), corrects / len(my))