t = int(input())
p = float(input())
import math
import statistics

def sigmoid(x):
  return 1 / (1 + math.exp(-x))

def check_student(s):
    min_n = 100
    for n in s:
        if n < min_n:
            min_n = n
    return min_n

k=0
for _ in range(t):
    students = [input() for x in range(100)]
    correct_questions = [0]*10000

    for student in students:
        for i, char in enumerate(student):
            if char == '1':
                correct_questions[i] += 1
    
    correct_questions = [(correct_questions[i], i) for i in range(10000)]
    mean = statistics.mean([x[0] for x in correct_questions])
    std = math.sqrt(sum([(x[0]-mean)**2 for x in correct_questions])/len(correct_questions)-1)
    difficulty = ([1-sigmoid((correct_questions[i][0]-mean)/std) for i in range(10000)])
    difficulty = ([(x,i) for i,x in enumerate(difficulty)])
    difficulty_index = [x[1] for x in sorted(difficulty)]
   
    students2 = []

    for i in range(100):
        students2.append([0]*200)
        count = 1
        correct= 0
        for j,index in enumerate(difficulty_index):
            if students[i][index] == '1':
                correct+=1
            if count >= 50:
                count=0
                #print(j)
                students2[i][(j//50)] = correct
                correct=0
            count+=1
            #students2[i][j] = students[i][index]
    


    possibilities = []
    for i, student in enumerate(students2):
        possibilities.append((check_student(student), i))
    
    possibilities = sorted(possibilities, reverse=True)
    k+=1
    print(f"Case #{k}: {possibilities[0][1]+1}")
