import sys
import os
import subprocess
import time
from filecmp import cmp

green = "\u001b[32m"
red = "\u001b[31m"
blue = "\u001b[35m"
reset = "\u001b[0m"

def compileCode(solver):
    extension = solver.split('.')
    extension = extension[len(extension) - 1]
    if (extension == "cpp"):
        os.system("g++ \"%s\" -o test -std=c++17 -static -O2 -lm" % solver)
    elif (extension == "c"):
        os.system("gcc \"%s\" -o test -static -O2 -lm" % solver)

solver, testCasesPath, timeLimit = sys.argv[1:]
timeLimit = float(timeLimit)
compileCode(solver)
print("Compiled Code", solver)

inputPath, outputPath = testCasesPath + "/input/", testCasesPath + "/output/"
testCases = os.listdir(inputPath)
accepted = True
for test in sorted(testCases, key=lambda x: int(x.split('_')[1])):
    startTime = time.time()
    os.system("./test < \"%s\" > auxOut" % (inputPath + test))
    # subprocess.run("./test < \"%s\" > auxOut" % (inputPath + test), shell=True, timeout=timeLimit)
    executionTime = time.time() - startTime

    verdict = "Accepted" if cmp("auxOut", outputPath + test) and executionTime <= timeLimit else "Wrong Answer" if executionTime <= timeLimit else "Time Limit Exceeded"
    color = green if verdict == "Accepted" else red if verdict == "Wrong Answer" else blue
    if verdict != "Accepted":
        accepted = False
        os.system("cat %s" % (outputPath + test))
        os.system("cat auxOut")

    print("%3d" % int(test.split("_")[1]), " - Verdict: ", color, verdict, reset, " | time: ", round(executionTime, 4), sep="")

if accepted:
    print(green, "ACCEPTED!!!!!", sep="")
else:
    print(red, "SOMETHING WENT WRONG!!!!!", sep="")
