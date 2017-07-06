
from socket import *

serverName = '127.0.0.1'

serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)

clientSocket.connect((serverName,serverPort))

sentence = raw_input('Input a lowercase sentence plz: ')

clientSocket.send(sentence)

modifiedSentence = clientSocket.recv(1024)

print 'Server Says: ', modifiedSentence

clientSocket.close()
