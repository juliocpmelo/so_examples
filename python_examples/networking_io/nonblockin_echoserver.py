import socket
import time
import sys

port = 65432 

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.setblocking(0)
	s.bind(('', port))
	s.listen(5)
	while True :
		try:
			conn, info = s.accept()
			data = conn.recv(1024)
			while data:
				print("received", repr(data))
				data = conn.recv(1024)
		
		except BlockingIOError:
			print ("waiting for connections")
			time.sleep(1);
	
