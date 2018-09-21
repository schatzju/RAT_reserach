import csv
import copy
#reads in removing and correcting files and edits csv file to remove these

def all_alpha(s):
	for char in s:
		if char.isalpha() == False:
			return False
	return True

#add words to dictionary from toAdd file
word_file = open("words.txt","r") 
words = []
for word in word_file:
	words.append(copy.deepcopy(word.rstrip()))
words_set = set(words)

word_file_append = open("words.txt","a") 

add_word_file = open("toAdd.txt", "r")

for word in add_word_file:
	if word.rstrip() not in words_set:
		word_file_append.write(word.rstrip())
		word_file_append.write('\n')


# { [eeew, gross] : [ew, gross] }

#correct entries

orig_list = []
cor_list = []

correct_file = open("toCorrect.txt","r") 
for line in correct_file:
	line = line.split()
	orig_list.append([line[0], line[1]])
	cor_list.append([line[4], line[5]])

orig_word_list = []
cor_word_list = []

correct_word_file = open("toCorrectWords.txt","r") 
for line in correct_word_file:
	line = line.split()
	orig_word_list.append(line[0])
	cor_word_list.append(line[2])

print(orig_word_list)
print(cor_word_list)


#remove remove words from csv file
remove_file = open("toRemove.txt","r") 
remove_words = []
for word in remove_file:
     remove_words.append(word.rstrip())

remove_words_set = set(remove_words)
print(remove_words_set)

change_count = 0

#read in csv file but ignore any that contain words from remove file
word_word_weight = {}
with open('assoc_17_08_22_18.csv') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	for row in csv_reader:
		row[0] = row[0].rstrip()
		row[1] = row[1].rstrip()
		if all_alpha(row[0]) and all_alpha(row[1]):
			row[0] = row[0].lower()
			row[1] = row[1].lower()

			comb_arr = [row[0], row[1]]

			for i in range(0, len(orig_list)):
				if comb_arr == orig_list[i]:
					print("changed1: " + row[0] + " " + row[1])
					change_count = change_count + 1
					row[0] = cor_list[i][0]
					row[1] = cor_list[i][1] 

			for i in range(0, len(orig_word_list)):
				if row[0] == orig_word_list[i]:
					print("changed2: " + row[0])
					change_count = change_count + 1
					row[0] = cor_word_list[i]
	
				if row[1] == orig_word_list[i]:
					print("changed3: " + row[1])
					change_count = change_count + 1
					row[1] = cor_word_list[i]

			comb_tup = (row[0], row[1])

			if row[0] not in remove_words_set and row[1] not in remove_words_set:
				if comb_tup in word_word_weight:
						word_word_weight[comb_tup] = word_word_weight[comb_tup] + int(row[2])
				else:
					word_word_weight[comb_tup] = int(row[2])
			else:
				print("changed4")
				change_count = change_count + 1

print()
print()
print("Number of changes (removed, corrected): " + str(change_count))

with open('assoc_17_08_23_18.csv', mode='w') as file:
	file_writer = csv.writer(file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
	for key, value in word_word_weight.items():
		row = [key[0], key[1], value]
		file_writer.writerow(row);







