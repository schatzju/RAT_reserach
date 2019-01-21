import copy

with open('data.txt') as f:
	lines = f.readlines()


new_arr = []
for word in lines:
	new_arr.append(copy.deepcopy(word.lower()))

for word in new_arr:
	print(word, end='')
