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
	sys.exit(0)	

signal.signal(signal.SIGINT, INT_handler)

memory = posix_ipc.SharedMemory("test", flags = posix_ipc.O_CREAT, mode = 0o777, size = 50)
mapped_memory = mmap.mmap(memory.fd, memory.size)
memory.close_fd()

s = "teste de escrita" + '\0'
cont = 0
print ("testing shared memory")
while True:
	mapped_memory.seek(0)
	s = "teste de escrita " + str(cont) +'\n\0'
	cont = cont + 1
  #encode é necessário para converter em bytes
	mapped_memory.write(struct.pack('>i',cont))
	time.sleep(1)


