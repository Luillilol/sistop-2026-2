#!/usr/bin/env python3

import threading as th
import random
import time

numero_sillas = 10



class Alumno(th.Thread):
	def __init__(self, id, semaforo, mutex):
		super().__init__()
		self.id = id
		self.semaforo = semaforo
		self.mutex = mutex
		self.numero_dudas = random.randint(1, 10)

	def run(self):
		semaforo.acquire()
		

		semaforo.release()



