in_file = open('input.txt','r',encoding='utf-8')
mylines = in_file.readlines()
Users = [set(),set(),set(),set()]
i=0
for line in mylines:
    values = list(map(str,line.split()))
    for k in values:
        Users[i].add(k)
    i=i+1        
m = len(Users[0]-Users[1]-Users[2]-Users[3])
u = len(Users[1]-Users[0]-Users[2]-Users[3])
s = len(Users[2]-Users[1]-Users[0]-Users[3])
g = len(Users[3]-Users[0]-Users[2]-Users[1])
unench = m+u+s+g
out_file = open('output.txt','w',encoding='utf-8')
out_file.write(str(unench))
in_file.close()
out_file.close()