import socket               
import sys
s = socket.socket()         
port = 8080               
#filename = "test.mp3"
# connect to the server on local computer
s.connect(('127.0.0.1', port))
filename = raw_input("Filename?\n")
f = open("2_"+filename, "wb")
# receive data from the server
#l = f.read(1024)
print s.recv(1024)

s.send(filename)
l = s.recv(1024)
while(l):
    f.write(l)
    l = s.recv(1024)
f.close()
# close the connection
s.close()  