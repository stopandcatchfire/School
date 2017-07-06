import hashlib, binascii, random, math


#x = base64.b16decode('00000000000000000000000000000000')  
#y = base64.b16decode('00000000000000000000000000000001') 
#x = bytearray([,1,0,3,0,16,35,8,50,59,124,99,12,3,64,8])
y = bytearray([0x66,0,0,0,0,0,0,0,0,0,0,0,0,0x03,0x06,0xf3])
#hx = ""
#hy = ""
#c = 0
k = 1
j = 15
#BLOCKSIZE = 65536



z = 6


text_file = open("hashOut" + str(z) + ".txt", "w")

while 1:
	 
	h2 = hashlib.sha256()
	h2.update(y)	
	hy = h2.hexdigest()
	hy = hy[::-1] #reverses hash to easily check reverse order
	sy = binascii.hexlify(y)	
	text_file.write("\n" + hy + " " + str(sy)) #prints hash and hex of byte array inputted into sha
	

	#should eliminate this mod, it is a hog, k == 10000000 then reset k to 0 duuuuhhhh
	if  0 == k%10000000:
		z += 1
		text_file = open("hashOut" + str(z) + ".txt", "w")


	


	
	y[j] = 1 + y[j]

	while y[j] == 255:
		y[j] = 0
		j -= 1
		y[j] = 1 + y[j]


	for j in (15,0):
		if y[j] == 0:
			break
		if y[j] == 255:
			y[j-1] = 1 + y[j-1]
			y[j] = 0
		

	k+=1



