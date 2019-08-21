# -*- coding: utf-8 -*-
import os
import signal
import time

pid = 0


param = os.sched_getparam(pid)
print("Parametros do processo " + str(param))

#muda os parametros do escalonador para um determinado pid
#os valores de prioridade suportados dependem da política
#de escalonamento corrente
#os.sched_setparam(pid, param)

#incrementa o "nice" do processo, dando uma forma
#de boost/downgrade na prioridade do mesmo, valores suportados no ubuntu 
#variam de -20 à 19, em alguns sistemas, esses limites são diferentes
#os.nice(10)

#muda a política de escalonamento para um determinado PID
#caso você não seja super usuário, a única política suportada
#são os.SCHED_OTHER(default), os.SCHED_IDLE e os.SCHED_BATCH
#as demais políticas suportadas: SCHED_FIFO (FCFS), SCHED_RR (Round Robin)
#e SCHED_SPORADIC tem que ser pré configuradas antes  de executar
#os.sched_setscheduler(pid, policy, param)


#muda a afinidade da cpu para um determinado processo
#para saber quais identificadores das CPUs você pode 
#visualizar o /proc/cpuinfo. Dessa forma você consegue
#restringir um processo a executar apenas em uma cpu ou em
#um determinado conjunto
#list_cpus = {0,1}
#os.sched_setaffinity(pid, list_cpus)
#os.sched_getaffinity(pid) #retorna quais cpus estao rodando esse processo

while(1):
	time.sleep(1)
