import socket
import select
import time
import sys

port = 65432 

read_list = []
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.setblocking(0)
	s.bind(('', port))
	s.listen(5)
	read_list.append(s)
	while True :
		readable, writeable, error = select.select(read_list,[],[])
		for sock in readable:
			if sock is s:
				conn, info = sock.accept()
				read_list.append(conn)
				print("connection received from ", info)
			else:
				data = sock.recv(1024)
				if data:
					print("received", repr(data))
					sock.send(data)
				else:
					sock.close()
					read_list.remove(sock)

		
