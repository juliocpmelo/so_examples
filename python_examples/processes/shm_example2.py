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

s = "teste de escrita" + '\0'
print ("testing shared memory")
while True:
	mapped_memory.seek(0)
  #encode é necessário para converter em bytes
	val_bytes = mapped_memory.read(4)
	read_val = struct.unpack('>i',val_bytes)
	print ("Linha escrita: " + str(read_val[0]))
	time.sleep(1);


