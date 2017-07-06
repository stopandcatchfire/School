from itertools import islice

#hashes = open('hashOut.txt')
sortedHashes = open('sortedHash.txt', 'w')
j = 0
hashes = open("hashOut0.txt")

#ghetto rigged merge-sort
for i in (1,100):
	lines = hashes.readlines()
	lines.sort()
	print (i)
	for line in lines:
		sortedHashes.write(line)
	hashes.close() #attempting to clear buffer
	hashes = open("hashOut" + str(i) + ".txt")
	

#lines.sort()

#for line in lines:
#	sortedHashes.write(line)

hashes.close()
sortedHashes.close()

