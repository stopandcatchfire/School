from socket import *




sPort = 12345		#predefined port #

sSocket = socket(AF_INET, SOCK_DGRAM) #creates server socket

sSocket.bind(('', sPort))	      ##binds socket to port (similar to C)

print 'Server ready to receive msg...'	#prints message to user

while 1:

	msg, cAddress = sSocket.recvfrom(2048)  ##receives 2048 bits of data through socket

	capMsg = msg.upper()		#caps msg

	sSocket.sendto(capMsg, cAddress) #sends back to client
