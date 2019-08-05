# -*- coding: utf-8 -*-
import time
import os
#exemplo para ser usado com system

print (os.getpid())
while True:
	print ('programa rodando em loop')
	time.sleep(1); #espera por 1 segundo

print ('Se chegar aqui podemos estar com problema')
