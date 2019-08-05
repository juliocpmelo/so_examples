
import threading
import time
import os

def thread_func():
	t = threading.currentThread()
	while True :
		print ("Sou o processo " + str(os.getpid()) + " na thread " + str(t.ident))
		time.sleep(1)


x = threading.Thread(target=thread_func, args=())
x.start()
while True :
	print ("Sou o processo principal " + str(os.getpid()) + " estou executando em paralelo à trhread" + str(x.ident))
	time.sleep(1)

# x.join()
