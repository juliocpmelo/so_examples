
import threading
import time
import os

var = 10

def thread_func():
	self_t = threading.currentThread()
	while True :
		print ("Sou o processo " + str(os.getpid()) + " na thread " + str(self_t.ident))
		print ("Valor de Var " + str(var))
		time.sleep(1)


t1 = threading.Thread(target=thread_func, args=())
t2 = threading.Thread(target=thread_func, args=())
t1.start()
t2.start()
while True :
	print ("Sou o processo principal " + str(os.getpid()) + " estou executando em paralelo às trhreads" + str(t1.ident) + " e " + str(t2.ident))
	var = var+1;
	time.sleep(1)

#
