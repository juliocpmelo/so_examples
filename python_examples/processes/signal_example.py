# -*- coding: utf-8 -*-
import os
import signal
import time

#em C essa funçao só recebe um argumento: o número do signal
def SIGINT_handler(sig_number, sig_stack):
	print ("nunca morrerei com ctrl-c")

#registra a funcao SIGINT_handler para ser executada
#quando o processo recebe um SIGINT. Assim,
#o processo nunca morre com ctrl-c.
signal.signal(signal.SIGINT, SIGINT_handler)

print ("Just saying, my pid: " + str(os.getpid()))

while True:
	print ("Invincible process")
	time.sleep(1)
