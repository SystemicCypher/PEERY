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
    #print"awaiting filename..."
    filename = c.recv(1024)
    #print "k"
    g = open("peercoin.config","r") 
    check = False
    #print filename
    
    for line in g:
        if filename in line:
            check = True
    g.close()
    
    if check == True:
        c.send('File received!')
    else:
        c.send("Not found")
    
    if check == True:
        f = open(filename, "rb")
        l = f.read(1024)
        while(l):
            c.send(l)
            l = f.read(1024)
        f.close()

    c.close()