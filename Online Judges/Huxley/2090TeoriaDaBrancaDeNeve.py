t = int(input())
home, personToEat = [], {}
while (t):
    command, person = input().split(':')
    if (command == "ENTROU"):
        toEat = int(input())
        if (person not in home):
            personToEat[person] = toEat
            home += [person]
            print(person, "entrou e gostaria de %dg de comida." % toEat)
        else:
            print(person, "ja estava em casa.")
    else:
        if (person in home):
            home.remove(person)
            personToEat[person] = 0
            print(person, "saiu de casa.")
        else:
            print(person, "nao estava na casa.")
    t -= 1

print("\nEstao na casa %d anoes:" % len(home))
total = 0
for p in home:
    print(p)
    total += personToEat[p]
print(total)
