import json
k = int(input())

main = json.loads(input())
in_ = [json.loads(input()) for x in range(k-1)]

ans = {}
for publication in main['publications']:
    p = 0
    for a in publication['articleCounts']:
        if a['year'] == '2017' or a['year'] == '2018':
            p += int(a['articleCount'])
    ans[publication['publicationNumber']] = [0, p, publication['publicationTitle']]
# print(ans)

for i in range(k-1):
    for article in in_[i]['paperCitations']['ieee']:
        if article['year'] == '2017' and article['publicationNumber'] in ans:
            ans[article['publicationNumber']][0] += 1
        if article['year'] == '2018' and article['publicationNumber'] in ans:
            ans[article['publicationNumber']][0] += 1
      # print(json.dumps(article, indent=4, sort_keys=True))
for a in ans:
    ans[a][0] = ans[a][0] / ans[a][1]

aa = []
for a in ans:
    aa += [[-ans[a][0], ans[a][2]]]
aa.sort()
for a in aa:
    print(a[1], ": %.2Lf" % (-a[0]), sep='')