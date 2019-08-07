import sys
import os
import filecmp
path = "D:/OneDrive/Programming/ProgramC/CodeForces/"

def EOF(f):
    current_pos = f.tell()
    file_size = os.fstat(f.fileno()).st_size
    return current_pos >= file_size

def inToAuxFile(auxFile, inputFile, stopKey):
    data, normal = [], 0
    while (True):
        try:
            line = inputFile.readline().decode("ascii")
            data += [line]
            if (stopKey in data[len(data) - 1].lower() or data[len(data) - 1] == ''):
                normal = data[len(data) - 1] != ''
                break
        except:
            normal = 0
            break
    for i in data[:len(data) - 1]:
        print(*i, file=auxFile, sep='', end='')
    auxFile.close()
    return(normal)

arg = sys.argv
os.system("g++ %s -o test -std=c++11" % (arg[1]))

inputFile = open("judgeIn", "rb")
inputFile.readline()
testCase = 1
while (True):
    auxIn = open("auxIn", "w")
    auxOut = open("auxOut", "w")
    ended = (inToAuxFile(auxIn, inputFile, "output") == 0)
    ended = max(ended, (inToAuxFile(auxOut, inputFile, "input") == 0))
    os.system("./test < auxIn > tryOut")
    tryOut = open("tryOut", "rb")
    print("Test Case %d:" % testCase, filecmp.cmp("auxOut", "tryOut"))
    testCase += 1
    if (ended): break
    tryOut.close()
inputFile.close()
