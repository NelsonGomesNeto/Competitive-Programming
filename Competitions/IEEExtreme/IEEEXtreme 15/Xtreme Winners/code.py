
a = "Team 1\n|Knapsackers@UNT\n|MoraSeekers\n|SurpriseTeam\n|CuSAT\n|DongskarPedongi\n|cofrades\n|viRUs\n|TeamName\n|TeamEPFL1\n|whatevs\n|WildCornAncestors\n|TheCornInTheFields\n|Aurora\n"
a = a.split('|')

def hehe(x):
    # s = sum(map(ord, x))
    s = list(map(ord, x))
    a = s[0]
    for aa in s[1:]:
        a -= aa
    a = -a
    return (x, a, chr(a))
    # return chr(a+70)
print(list(map(hehe, a)))
# print(''.join(list(map(hehe, a))))

#print('psaSprATgsraUsmNmEtedCCoor'.find(input()[3:5])//2+2)
print(" ǘ֭ѡӤƠ׿͇ǹ̈˟̂۔ۢɪ".find(chr(sum(map(ord,input())))))