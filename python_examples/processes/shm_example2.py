# -*- coding: utf-8 -*-
import time
import os, sys
import mmap
import signal
import posix_ipc

mapped_memory = None

def INT_handler(sig_num, arg):
	if mapped_memory != None:
		mapped_memory.close()
	sys.exit(0)

signal.signal(signal.SIGINT, INT_handler)

memory = posix_ipc.SharedMemory("test")
mapped_memory = mmap.mmap(memory.fd, memory.size)
memory.close_fd()

s = "teste de escrita" + '\0'
cont = 0
print "testing shared memory"
while True:
	mapped_memory.seek(0)
  #encode é necessário para converter em bytes
	print "Linha escrita: " + mapped_memory.readline()
	time.sleep(1);


