# -*- coding: utf-8 -*-
import time
import os

print "sou o processo pai!, ainda nao tenho filhos"
val = os.fork() #fork cria um processo a partir do processo pai

if val == 0 :
	while True:
		print 'sou o filho ficarei esperando para sempre aqui'
		time.sleep(1)
else:
	while True:
		print 'sou o processo pai ficarei esperando para sempre aqui'
		time.sleep(1)
