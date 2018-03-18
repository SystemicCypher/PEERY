import socket 
import sys              

s = socket.socket()         
print "Socket successfully created"
 
port = 8080               
 
s.bind(('', port))        
print "socket bound to %s" %(port)
s.listen(5)     
print "socket is listening"           

while True:
 
    # Establish connection with client.
    c, addr = s.accept()     
    print 'Got connection from', addr

    
    # send a thank you message to the client. 
    c.send('File received!')
    filename = c.recv(1024)
    f = open(filename, "rb")
    l = f.read(1024)
    while(l):
        c.send(l)
        l = f.read(1024)
    f.close()
    c.close()