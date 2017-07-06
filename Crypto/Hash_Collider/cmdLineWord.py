x = "hashOut50.txt"
c = open("cmdLine.txt", "w")
c.write(x)
for i in range(51,100):
	
	x = " hashOut" + str(i) + ".txt"	
	c.write(x)


c.close()
