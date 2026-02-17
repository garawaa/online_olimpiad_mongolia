from operator import itemgetter
in_file = open('input.txt','r',encoding='utf-8')
mylines = in_file.readlines()
bgllg = {}
#keys = ['ner','ovog','regnum','utas','baig','ognoo']
for line in mylines:
    values = line.split(',')
    if values[4] in bgllg.keys():
        bgllg[values[4]].add(values[2])
    else:
        bgllg[values[4]] = set()
        bgllg[values[4]].add(values[2])
regs = []
for key in bgllg:
    regs.append({'baiguullaga':key,'num':len(bgllg[key])})
       
out_file = open('output.txt','w',encoding='utf-8')
#a = sorted(regs, key=lambda k: (-k['num'], k['baiguullaga']))
regs.sort(key=itemgetter('baiguullaga'))
regs.sort(key=itemgetter('num'), reverse=True)
for row in regs:
    out_file.write(row['baiguullaga']+" "+str(row['num'])+"\n")
in_file.close()
out_file.close()