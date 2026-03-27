#!/usr/bin/env python3

import threading as th
import random
import time

numero_sillas = 10



class Alumno(th.Thread):
	def __init__(self, id, sillas, turno, condicion):
		super().__init__()
		self.id = id
		self.silla = sillas
		self.turno = turno
		self.condicion = condicion
		self.numero_dudas = random.randint(1, 10)

	def run(self):
		with self.silla:

			print(f"El alumno {self.id} entró al cubiculo")

			self.resolver_dudas()

		print(f"El alumno {self.id} salió del cubiculo")

	def resolver_dudas(self):
		while self.numero_dudas != 0:
			
			with self.turno:
				self.condicion.notify()
				print(f"El alumno {self.id} está relaizando resolviendo una duda")
				self.condicion.wait()
				self.numero_dudas -= 1
							
			time.sleep(1)

		print(f"El alumno {self.id} resolvio todas sus dudas") 

class Profesor(th.Thread):
	def __init__(self, condicion):
		super().__init__()
		self.condicion = condicion

	def run(self):
		with self.condicion:
			while True:
				print(f"El Profesor está resolviendo una duda")
				
				time.sleep(1)

				self.condicion.notify()
				print(f"El Profesor terminó con una duda")
				self.condicion.wait()			

def main():
	
	numero_sillas = th.Semaphore(10)

	turno = th.Lock()

	condicion = th.Condition(turno)
	
	id_alumno = 1	

	profesor = Profesor(condicion)
	profesor.daemon = True
	profesor.start()


	try:
		while True:
			alumno = Alumno(id_alumno, numero_sillas, turno, condicion)
			alumno.start()
			id_alumno += 1
	except KeyboardInterrupt:
		print("finalizacion")


main()
