import sys
import os
import time
from filecmp import cmp

def compileCode(solver):
    extension = solver.split('.')
    extension = extension[len(extension) - 1]
    if (extension == "cpp"):
        os.system("g++ \"%s\" -o test -std=c++17 -O2 -lm" % solver)
    elif (extension == "c"):
        os.system("gcc \"%s\" -o test -O2" % solver)

solver, testCasesPath, timeLimit = sys.argv[1:]
timeLimit = float(timeLimit)
compileCode(solver)
print("Compiled Code", solver)
inputPath, outputPath = testCasesPath + "/input/", testCasesPath + "/output/"
testCases = os.listdir(inputPath)
accepted, fails = True, 0
for test in sorted(testCases, key=lambda x: int(x.split('_')[1])):
    startTime = time.time()
    os.system("./test < \"%s\" > auxOut" % (inputPath + test))
    executionTime = time.time() - startTime
    verdict = "Accepted" if cmp("auxOut", outputPath + test) and executionTime <= timeLimit else "Wrong Answer" if executionTime <= timeLimit else "Time Limit Exceeded"
    if verdict != "Accepted": accepted, fails = False, fails + 1
    print(test.split("_")[1], "- Verdict:", verdict, "| time:", round(executionTime, 4))
if accepted:
    print("ACCEPTED!!!!!!!!")
else:
    print("%d test cases failed" % fails)