

f=open("SCOWL.txt", 'r')
f2=open("SCOWLCleaned.txt", "w+")

f1 = f.readlines()
for x in f1:
	if "'" not in x:
		f2.write(x.lower())
