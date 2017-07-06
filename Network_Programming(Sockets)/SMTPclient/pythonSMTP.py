
from socket import *

msg = "\r\n I love computer networks!"

endmsg = "\r\n.\r\n"

# Choose a mail server (e.g. Google mail server) and call it mailserver 

mailserver = 'gaia.ecs.csus.edu'

# Create socket called clientSocket and establish a TCP connection with mailserver 

serverPort = 25

clientSocket = socket(AF_INET, SOCK_STREAM)

clientSocket.connect((mailserver, serverPort))

# break


recv = clientSocket.recv(1024)

print recv

if recv[:3] != '220':
     print '220 reply not received from server.'

# Send HELO command and print server response.

heloCommand = 'HELO Alice\r\n'

clientSocket.send(heloCommand)

recv1 = clientSocket.recv(1024)

print recv1

if recv1[:3] != '250':
    print '250 reply not received from server.'

# Send MAIL FROM command and print server response.
# Fill in start
frm = ("MAIL FROM: <mwantz@comcast.net>\r\n")

clientSocket.send(frm)

recv2 = clientSocket.recv(1024)

print recv2

# Fill in end
# Send RCPT TO command and print server response.
# Fill in start

rcpt = ("RCPT TO: <mwantz@comcast.net>\r\n")
clientSocket.send(rcpt)

rcv3 = clientSocket.recv(1024)

print rcv3

# Fill in end
# Send DATA command and print server response.
# Fill in start
data = ("DATA\r\n")

clientSocket.send(data)

rcv4 = clientSocket.recv(1024)

print rcv4
# Fill in end
# Send message data.
# Fill in start

msg2 = ("This is nick just testing this thing out.  Turns out I can send stuff from other peoples mail addresses.  Sketchy lol.\r\n")

clientSocket.send(msg2)


#rcv = clientSocket.recv(1024)
#print rcv

# Fill in end
# Message ends with a single period.
# Fill in start
clientSocket.send(endmsg)


rcv5 = clientSocket.recv(1024)

print rcv5



# Fill in end
# Send QUIT command and get server response.
# Fill in start
q = ("QUIT\r\n")
clientSocket.send(q)

rcv6 = clientSocket.recv(1024)

print rcv6
# Fill in end

clientSocket.close()

