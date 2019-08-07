DEBUG = 0
run = 0
while (True):
	advancedClasses, maximumClasses = map(int, input().split())
	if (advancedClasses == 0 and maximumClasses == 0):
		break
	if (run > 0):
		print()
	run += 1
	preGraph, classes = [], []
	for i in range(advancedClasses):
		line = input().split()
		line.pop(1)
		preGraph += [line]
		classes += line
	classes = ordered(classes)
	stringToInt = dict(zip(classes, range(len(classes))))
	intToString = dict(zip(range(len(classes)), classes))
	if (DEBUG):
		print("PreGraph:", preGraph)
		print("Maps:", stringToInt, intToString)

	graph = [[] for i in range(len(classes))]
	for i in preGraph:
		for j in i[1:]:
			graph[stringToInt[j]] += [stringToInt[i[0]]]

	# Building inDegree
	inDegree = [0] * len(classes)
	for u in graph:
		for v in u:
			inDegree[v] += 1
	if (DEBUG):
		print(inDegree)

	watched, semester, courses = 0, 0, [[] for i in range(len(classes))]
	finalCourses = [[] for i in range(len(classes))]
	while (watched < len(classes)):
		line = []
		for i, quantity in enumerate(inDegree):
			if (quantity == 0):
				line += [intToString[i]]

		#line.sort()
		if (DEBUG):
			print(semester, line, inDegree, courses)
		for i in line:
			courses[semester] += [i]
			if (len(courses[semester]) == maximumClasses):
				break
		semester += 1
		for i in courses[semester - 1]:
			watched += 1
			inDegree[stringToInt[i]] -= 1
			for u in graph[stringToInt[i]]:
				inDegree[u] -= 1


	if (DEBUG == 2):
		print("courses", end=' ')
		for i in courses:
			for j in i:
				print(j, end=' ')
			print()

	print("Formatura em", semester, "semestres", end='')
	semester = 1
	for i in courses:
		if (len(i) == 0):
			break
		print("\nSemestre", semester, ":", end='')
		semester += 1
		for j in i:
			print(" ", j, sep='', end='')
