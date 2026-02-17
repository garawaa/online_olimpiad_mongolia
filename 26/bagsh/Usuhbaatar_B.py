
def get_node(s):
	node = 1
	for c in s:
		if c == '1':
			node *= 2
		elif c == '2':
			node *= 2
			node += 1
		elif c == 'R':
			node += 1
		elif c == 'L':
			node -= 1
		elif c == 'U':
			node //= 2
	return node


def get_level(node):
	level = 0
	while node > 0:
		level += 1
		node //= 2
	return level


def dist(a, b):
	la = get_level(a)
	lb = get_level(b)
	if la > lb:
		a, b = b, a
		la, lb = lb, la

	for i in range(lb - la):
		b //= 2

	ret = abs(b - a) + lb - la
	cnt = 0
	while a > 1:
		temp = abs(b - a) + lb - la + cnt
		ret = min(temp, ret)
		b //= 2
		a //= 2
		cnt += 2

	return ret

a = input()
b = input()

print(dist(get_node(a), get_node(b)))

