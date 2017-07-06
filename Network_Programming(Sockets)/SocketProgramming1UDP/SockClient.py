from socket import *

sName = '127.0.0.1'     #server points to local server.

sPort = 12345     #predefined server port 

cSocket = socket(AF_INET, SOCK_DGRAM)  #defines UDP socket 
msg = raw_input('Send a lowercase sentence: ')

cSocket.sendto(msg,(sName, sPort))   #sends msg to server

capMsg, sAddress = cSocket.recvfrom(2048)  #string capMsg gets 2048 bits frm server.

print capMsg #prints modified msg

cSocket.close()  #closes UDP socket
