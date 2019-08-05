# -*- coding: utf-8 -*-
import os
import signal

pid = input("Informe um pid: ")

#mata o processo
os.kill(pid, signal.SIGKILL)
#interropme o processo (msm que ctrl-c)
#os.kill(pid, signal.SIGINT)
#pausa o processo
#os.kill(pid, signal.SIGSTOP)
#retoma o processo
#os.kill(pid, signal.SIGCONT)
#envia um sinal para si mesmo
