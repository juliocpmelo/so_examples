# -*- coding: utf-8 -*-
import time
import os, sys
import mmap
import signal
import posix_ipc
import struct

mapped_memory = None

def INT_handler(sig_num, arg):
	if mapped_memory != None:
		mapped_memory.close()
	sys.exit(0)

signal.signal(signal.SIGINT, INT_handler)

memory = posix_ipc.SharedMemory("test")
mapped_memory = mmap.mmap(memory.fd, memory.size)
memory.close_fd()

sem = posix_ipc.Semaphore("test_sem")

s = "teste de escrita" + '\0'
print ("testing shared memory")
while True:
	mapped_memory.seek(0)
	#regiao critica, usando memoria compartilhada 
	sem.acquire()
	val_bytes = mapped_memory.read(4)
	sem.release()
	#fim regiao crítica
	read_val = int.from_bytes(val_bytes, byteorder='big')
	print ("Linha escrita: " + str(read_val))
	time.sleep(1);


