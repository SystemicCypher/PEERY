import socket               
import sys
import time


def client(filename):
# = socket.socket()         
#port = 8080               
# receive data from the server
#time.sleep(10)
#if(filename != ""):
    s = socket.socket()         
    port = 8080 
 
    s.connect(('127.0.0.1', port))
    s.send(filename)


    check = s.recv(1024)

    if(check != "Not found"):
        f = open("2_"+filename, "wb")
        l = s.recv(1024)
        while(l):
            f.write(l)
            l = s.recv(1024)
        f.close()
    else:
        print "Target doesn't have that file\n"


    # close the connection
    s.close() 