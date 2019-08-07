# -*- coding: utf-8 -*-
import time
import os
import mmap
import signal
import posix_ipc
import sys
import struct

mapped_memory = None

def INT_handler(sig_num, arg):
	if mapped_memory != None: 
		mapped_memory.close()
		posix_ipc.unlink_shared_memory("test")
		#desaloca a o semaforo	
	sem.close()
	sys.exit(0)	

signal.signal(signal.SIGINT, INT_handler)

memory = posix_ipc.SharedMemory("test", flags = posix_ipc.O_CREAT, mode = 0o777, size = 50)
mapped_memory = mmap.mmap(memory.fd, memory.size)
memory.close_fd()

sem = posix_ipc.Semaphore("test_sem", flags = posix_ipc.O_CREAT, mode = 0o777,  initial_value=1)

s = "teste de escrita" + '\0'
cont = 0
print ("testing shared memory")
while True:
	print ("writing " + str(cont) + " val " + str(sem.value))
	mapped_memory.seek(0)

	print ("writing " + str(cont))
	s = "teste de escrita " + str(cont) +'\n\0'
	cont = cont + 1
	#regiao critica, usando memoria compartilhada
	sem.acquire()
	print ("writing " + str(cont))
	mapped_memory.write(cont.to_bytes(4,byteorder='big'))
	sem.release()
	#fim da regiao critica
	time.sleep(1)



