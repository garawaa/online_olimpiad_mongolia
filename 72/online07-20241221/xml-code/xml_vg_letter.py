#python3
import sys
from collections import deque

def check(test):
    test = '>' + test + '<'
    testlist = test.split('><')
    if testlist[0] != '' or testlist[-1] != '':
        return False
    testlist = testlist[1:-1]
    for s in testlist:
        if '<' in s or '>' in s:
            return False
    q = deque()
    for s in testlist:
        if s[0] != '/':
            q.append(s)
        elif not q or q.pop() != s[1:]:
            return False
    if q:
        return False
    return True

fin = open('input.txt')
fout = open('output.txt', 'w')
s = fin.readline().strip()
alph = 'qwertyuiopasdfghjklzxcvbnm'
for i in range(len(s)):
	if s[i] in alph:
		for c in alph:
			test = s[:i] + c + s[i + 1:]
			if check(test):
				print(test, file = fout)
				fout.close()
				sys.exit()
