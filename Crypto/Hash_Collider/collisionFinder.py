

sortedHash = open('sortedHash3.txt')
	

x = ""
y = "stahp"
c = 0
k = 0




for line in sortedHash:
	
	x = line
	
	for i in range(len(x)):
		
		if y[i] == x[i]:
			c += 1

		else:
			break
		
	if c > k:	
		if c < 68:
			k = c
			print ("x: " + x + "\ny: " + y + "\nk: " + str(k))
	
	
	c = 0
	y = line
	
