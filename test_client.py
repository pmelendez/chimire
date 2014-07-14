#!/usr/bin/python

import select
import socket
import sys
from threading import Thread
from time import sleep

TCP_IP = '127.0.0.1'
TCP_PORT = 14095
BUFFER_SIZE=1024
LOGIN_MSG = "(System,Login){user:b,password:b}"

global s
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.setblocking(0)
#s.settimeout(1)
s.send(LOGIN_MSG)

global cwhite 
global cyellow 
global cgreen 
global cred  

cwhite = '\033[0m'
cyellow =  '\033[93m'
cgreen = '\033[92m'
cred = '\033[91m' 

global active
global prompt
prompt = "Please enter a message:" 
active = 1

def ReadingThread():
	while active:
		try:
			data= s.recv(BUFFER_SIZE)
                	print cyellow + "--Incoming message:", data, cwhite 
		except:
			continue

thread = Thread(target = ReadingThread)
thread.start()

while 1:
	try:
		sleep(0.1)
		print prompt
		newmsg=raw_input()
		s.send(newmsg)
		
	except KeyboardInterrupt:
		print "\n",cred,"Quitting",cwhite
		active = 0
		s.close()
		exit()
	except:
		print "There was an exception",sys.exc_info()[0]
